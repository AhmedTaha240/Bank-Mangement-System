#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsShowFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card: ";
		cout << "\n____________________________________";
		cout << "\nCountry    :" << Currency.Country();
		cout << "\nCode       :" << Currency.CurrencyCode();
		cout << "\nName       :" << Currency.CurrencyName();
		cout << "\nRate(1$) = :" << Currency.Rate();
		cout << "\n____________________________________";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t   Find Currency Screen");

		short Answer;
		cout << "\nFind By: [1] Code or [2] Country ?  ";
		Answer = clsInputValidate::ReadIntNumebrBetween(1, 2);

		if (Answer == 1)
		{
			string CurrencyCode;
			cout << "\nPlease Enter Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else
		{
			string Country;
			cout << "\nPlease Enter Country Name: ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	}
};

