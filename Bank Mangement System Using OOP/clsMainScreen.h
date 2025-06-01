#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"

#include "clsLoginRegisterScreen.h"

#include "clsCurrencyExchangeScreen.h"

#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, 
		eFindClient = 5, eShowTransactionsMenue = 6, eManageUsers = 7, 
		eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
	};

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	} 
	
	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientsScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionMenue();
	}
	static void _ShowManageUsersMenue()
	{
		clsManageUsersScreen::ShowManageUsersMenue();
	}
	static void _ShowLoginRegister()
	{
		clsLoginRegisterScreen::ShowLoginRegister();
	}
	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchangeMenue();
	}
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");

		//clsLoginScreen::ShowLoginScreen();
	}

	static void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...";
		system("pause >0");
		ShowMainMenue();
	}

	static void _PerformMainMenueOption(enMainMenueOptions MainMenueOptions)
	{
		switch (MainMenueOptions)
		{
		case clsMainScreen::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}

		case clsMainScreen::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case clsMainScreen::eDeleteClient:
		{
			system("cls");
			_ShowDeleteClientsScreen();
			_GoBackToMainMenue();
			break;
		}

		case clsMainScreen::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}

		case clsMainScreen::eFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		}
		
		case clsMainScreen::eShowTransactionsMenue:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}

		case clsMainScreen::eManageUsers:
		{
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;
		}

		case clsMainScreen::eLoginRegister:
		{
			system("cls");
			_ShowLoginRegister();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eCurrencyExchange:
		{
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;
		}
		case clsMainScreen::eExit:
		{
			system("cls");
			_Logout();

			//clsLoginScreen::ShowLoginScreen();
			break;
		}
		}
	}

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 10]? ";
		short Choice = clsInputValidate::ReadIntNumebrBetween(1, 10, "Enter Number between 1 to 10?  ");
		return Choice;
	}

public:

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "===============================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===============================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===============================================\n\n";
		
		_PerformMainMenueOption(enMainMenueOptions(_ReadMainMenueOption()));
	}
};

