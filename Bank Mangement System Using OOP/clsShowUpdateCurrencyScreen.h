#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsShowUpdateCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n\nCurrency Card: ";
		cout << "\n____________________________________";
		cout << "\nCountry    :" << Currency.Country();
		cout << "\nCode       :" << Currency.CurrencyCode();
		cout << "\nName       :" << Currency.CurrencyName();
		cout << "\nRate(1$) = :" << Currency.Rate();
		cout << "\n____________________________________";
	}

	static float _ReadRate()
	{
		float NewRate;

		cout << "\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadDblPositiveNumebr();
		
		return NewRate;
	}

public:
	static void ShowUpdateCurrencyScreen()
	{
		_DrawScreenHeader("\t   Update Currency Screen");

		string CurrencyCode;
		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		while (!Currency.IsCurrencyExists(CurrencyCode))
		{
			cout << "\nThe Currency in Not Found, ";
			cout << "\nPlease Enter Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		_PrintCurrencyCard(Currency);

		char Answer = 'n';
		cout << "\n\nAre you sure you want to update the rate of this Currency [Y / N]?  ";
		cin >> ws >> Answer;

		if (tolower(Answer) == 'y')
		{
			cout << "\n\nUpdate Currency Rate: ";
			cout << "\n\n____________________________";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)";
			
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency Rate Updated was Cancelled :-(";
		}
	}
};

