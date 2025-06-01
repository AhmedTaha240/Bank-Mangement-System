#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsListUsersScreen : protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUser User)
	{
		cout << setw(8) << left << "" << "| " <<
			setw(12) << left << User.UserName;
		cout << "| " << setw(25) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.Permissions;
	}


public:
	static void ShowListUsersScreen()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\t   User List Screen";
		string SubTitle = "\t     (" + to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);
		
		cout << "\n\t_______________________________________________________"
			"_______________________________________________\n\n";

		cout << setw(8) << left << "" 
		  	 << "| " << setw(12) << left << "UserName";
		cout << "| " << setw(25) << left << "Full Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(12) << left << "Permissions";

		cout << "\n\t_______________________________________________________"
			"_______________________________________________\n\n";

		if (vUsers.size() == 0)
		{
			cout << "\t\t\t\tNo Users Available In the System!";
		}
		else
		{
			for (clsUser& U : vUsers)
			{
				_PrintUserRecordLine(U);
				cout << endl;
			}
		}
		cout  << "\n\t_______________________________________________________"
			"_______________________________________________\n\n";
	}
};

