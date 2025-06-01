#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsShowCurrenciesListScreen.h"
#include "clsShowFindCurrencyScreen.h"
#include "clsShowUpdateCurrencyScreen.h"
#include "clsShowCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyMenue {enListCurrencies = 1, enFindCurrency = 2, enUpdateRate = 3,
	enCurrencyCalculator = 4, enMainMenue = 5};

	static void _GoBackToCurrenciesMenue()
	{
		cout << "\n\nPress any key to go back to Currencies Menue...";
		system("pause > 0");
		ShowCurrencyExchangeMenue();
	}

	static short _ReadCurrenciesMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 5]? ";
		short Choice = clsInputValidate::ReadIntNumebrBetween(1, 5, "Enter Number between 1 to 5?  ");
		return Choice;
	}

	static void _ShowCurrenciesListScreen()
	{
		//cout << "\nList Curriencies Screen Will be here.\n";
		clsShowCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	
	static void _ShowFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen Will be here.\n";
		clsShowFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	
	static void _ShowUpdateRateScreen()
	{
		//cout << "\nUpdate Rate Screen Will be here.\n";
		clsShowUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
	}
	
	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen Will be here.\n";
		clsShowCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyExchangeMenue(enCurrencyMenue CurrencyMenue)
	{
		switch (CurrencyMenue)
		{
		case clsCurrencyExchangeScreen::enListCurrencies:
		{
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenue();
			break;
		}
		case clsCurrencyExchangeScreen::enFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenue();
			break;
		}
		case clsCurrencyExchangeScreen::enUpdateRate:
		{
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrenciesMenue();
			break;
		}
		case clsCurrencyExchangeScreen::enCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenue();
			break;
		}
		case clsCurrencyExchangeScreen::enMainMenue:
		{
			system("cls");
			break;
		}
		}
	}

public:
	static void ShowCurrencyExchangeMenue()
	{
		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "===============================================\n";
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Main Screen\n";
		cout << setw(37) << left << "" << "===============================================\n";
		
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";

		cout << setw(37) << left << "" << "===============================================\n";

		_PerformCurrencyExchangeMenue(enCurrencyMenue(_ReadCurrenciesMenueOption()));
	}
};

