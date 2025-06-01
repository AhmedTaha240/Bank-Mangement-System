#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"

#include "clsTransferScreen.h"

#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen 
{
private:
	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithdraw = 2,eShowTotalBalance = 3,
		 eTransfer = 4 , eTransferLog = 5 ,eShowMainMenue = 6
	};

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]? ";
		short Choice = clsInputValidate::ReadIntNumebrBetween(1, 6, "Enter Number between 1 to 6 ! ");
		return Choice;
	}

	static void _ShowDepositScreen()
	{
		//cout << "\n Deposit Screen will be here. \n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\n Deposit Screen will be here. \n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalanceScreen()
	{
		//cout << "\n TotalBalance Screen will be here. \n";
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		//cout << "\n Deposit Screen will be here. \n";
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		//cout << "\n Deposit Screen will be here. \n";
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Trasnsactions Menue...";
		system("pause > 0");
		ShowTransactionMenue();
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions)
	{
		switch (TransactionsMenueOptions)
		{
		case clsTransactionsScreen::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsScreen::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsScreen::eShowTotalBalance:
		{
			system("cls");
			_ShowTotalBalanceScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsScreen::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsScreen::eTransferLog:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsTransactionsScreen::eShowMainMenue:
		{
			//ShowMainMenue();    // Error: error C3861: 'ShowMainMenue': identifier not found
			
			//do nothing here the main screen will handle it :-) ;
			break;
		}

		}
	}
public:
	static void ShowTransactionMenue()
	{
		// you can using ChekcAccessPermission() which is found in clsUser.h
		/* if (!CurrentUser.ChekcAccessPermission(clsUser::enPermissions::pTransactions))
		{
			cout << "\nAccess Denied! Contact your Admin\n";
			return;
		}*/
								// or
		// you can using a static method CheckAccessRights() which is found in clsScreen.h 
		if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "  ===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
		cout << setw(37) << left << "" << "  ===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}
};

