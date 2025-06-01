#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "Global.h"

#include "clsMainScreen.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		string UserName, Password;

		bool IsLoginFailed = false;
		short FailedLoginCount = 0;

		do
		{
			if (IsLoginFailed)
			{
				FailedLoginCount++;
				cout << "\nInvalid UserName/Password!\n";
				cout << "You have " << (3- FailedLoginCount) 
					 << " Trial(s) to login.\n\n";

				if (FailedLoginCount == 3)
				{
					cout << "\nYou are Locked after 3 failed trails.\n";
					return false;
				}
			}

			cout << "Enter Username?  ";
			UserName = clsInputValidate::ReadString();

			cout << "Enter Password?  ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			IsLoginFailed = CurrentUser.IsEmpty();

		} while (IsLoginFailed);

		CurrentUser.RegisterLogIn();

		clsMainScreen::ShowMainMenue();
		return true;
	}
	
public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t        Login Screen");
		return _Login();

		// You can use Recursion instead of using while loop in int main()
		//ShowLoginScreen();   
		
		// You can call the method here instead of calling it inside _Login()
		//clsMainScreen::ShowMainMenue();
	}

	
};

