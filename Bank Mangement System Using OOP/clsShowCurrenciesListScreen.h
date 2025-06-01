#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsShowCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyInfo(clsCurrency Currency)
	{
		cout << setw(8) << "" << "| " << setw(35) << left << Currency.Country();
		cout << "| " << setw(10) << left << Currency.CurrencyCode();
		cout  << "| " << setw(45) << left << Currency.CurrencyName();
		cout <<  "| " << setw(10) << left << Currency.Rate();
	}

public:
	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies =  clsCurrency::GetCurrenciesList();

		string Title = "\t    Currencies List Screen";
		string SubTitle = "\t\t(" + to_string(vCurrencies.size()) + ") Currency.";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t____________________________________________________"
			<< "_________________________________________________________\n\n";

		cout << setw(8) << "" << "| " << setw(35) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(45) << left << "Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";

		cout << "\n\t____________________________________________________"
			<< "_________________________________________________________\n\n";

		if (vCurrencies.size() == 0)
		{
			cout << "\n\t\t\t\tNo Currencies Available In The System\n";
		}
		else
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyInfo(Currency);
				cout << endl;
			}
		}
	}
};

