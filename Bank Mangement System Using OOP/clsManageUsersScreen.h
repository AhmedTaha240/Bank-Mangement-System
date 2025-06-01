#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersMenueOptions {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5,
		eMainMenue = 6
	};

	static short _ReadManageUsersMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]? ";
		short Choice = clsInputValidate::ReadIntNumebrBetween(1, 6, "Enter Numebr between 1 to 6 ! ");
		return Choice;
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << "\nPress any key to go back to Manage Users Menue...";
		system("pause >0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		//cout << "\n List Users Screen will be here. \n";
		clsListUsersScreen::ShowListUsersScreen();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "\n Add New User Screen will be here. \n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "\n Delete User Screen will be here. \n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		//cout << "\n Update User Screen will be here. \n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		//cout << "\n Find User Screen will be here. \n";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOptions)
	{
		switch (ManageUsersMenueOptions)
		{
		case clsManageUsersScreen::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		case clsManageUsersScreen::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		case clsManageUsersScreen::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		case clsManageUsersScreen::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		case clsManageUsersScreen::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		case clsManageUsersScreen::eMainMenue:
		{
			//do nothing here the main screen will handle it :-) ;
			break;
		}

		}
	}

public:

	static void ShowManageUsersMenue()
	{
		// you can using ChekcAccessPermission() which is found in clsUser.h
		/* if (!CurrentUser.ChekcAccessPermission(clsUser::enPermissions::pManageUsers))
		{
			cout << "\nAccess Denied! Contact your Admin\n";
			return;
		}*/
									// or
		// you can using a static method CheckAccessRights() which is found in clsScreen.h 
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("\t  Manage Users Screen");

		cout << setw(37) << left << "" << "  ===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
		cout << setw(37) << left << "" << "  ===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}
};

