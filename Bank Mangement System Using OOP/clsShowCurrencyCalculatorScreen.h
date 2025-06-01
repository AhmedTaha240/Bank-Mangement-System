#pragma once
#include <iostream>
#include <string>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsString.h"

using namespace std;

class clsShowCurrencyCalculatorScreen : protected clsScreen
{
private:

	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float Amount = clsInputValidate::ReadDblPositiveNumebr();
		return Amount;
	}

	static void _PrintCurrencyCard(clsCurrency Currency , string Title = "Currency Card: ")
	{
		cout << "\n" << Title;
		cout << "\n____________________________________";
		cout << "\nCountry    :" << Currency.Country();
		cout << "\nCode       :" << Currency.CurrencyCode();
		cout << "\nName       :" << Currency.CurrencyName();
		cout << "\nRate(1$) = :" << Currency.Rate();
		cout << "\n____________________________________\n\n";
	}

	static clsCurrency _GetCurrency(string Message)
	{
		string CurrencyCode;

		cout << "\n" << Message;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExists(CurrencyCode))
		{
			cout << "\nThe Currency Code is Not Found, Enter another Currency Code! ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		if (Currency2.CurrencyCode() == Currency1.CurrencyCode())
		{
			cout << "\nYou can't Exchange Currency to the Same Currency";
			return;
		}

		if (Currency1.CurrencyCode() != "USD")
		{
			_PrintCurrencyCard(Currency1, "Convert From");
			float AmountInUSD = Currency1.ConvertToUSD(Amount);

			cout << Amount << " " << Currency1.CurrencyCode() << " = "
				<< AmountInUSD << " USD\n";
		}

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConvert From USD To\n";
		
		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount,Currency2);

		cout << Amount << " " << Currency1.CurrencyCode() << " = "
			<< AmountInCurrency2 << " " << Currency2.CurrencyCode();
	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Contiune = 'y';

		while (tolower(Contiune) == 'y')
		{
			system("cls");
			_DrawScreenHeader("\t    Currency Calculator Screen");
			
			clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("Please Enter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? [Y / N] ?  ";
			cin >> ws >> Contiune;
		}
	}
};

