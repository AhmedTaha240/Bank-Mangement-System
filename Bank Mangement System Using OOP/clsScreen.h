#pragma once
#include <iostream>

#include "clsUser.h"
#include "Global.h"

#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\n\t\t\t\t\t_________________________________________";
		cout << "\n\n\t\t\t\t\t  " << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t  " << SubTitle;
		}
		cout << "\n\t\t\t\t\t_________________________________________\n\n";

		// Extension 01 - Adding Date and Logged In User to All Screens 
		cout << "\n\t\t\t\t\tUser: " << CurrentUser.UserName;
		
		if (CurrentUser.UserName != "")
		{
			cout << "\t\t Date: " << clsDate::DateToString(clsDate());
		}
		else
		{
			cout << "\t\t\t Date: " << clsDate::DateToString(clsDate());

		}
		
		cout << "\n\n";
	}

	///////// Check Permissions of User 
	static bool CheckAccessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.ChekcAccessPermission(Permissions))
		{
			cout << "\n\t\t\t\t\t______________________________________________";
			cout << "\n\n\t\t\t\t\t    Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________________\n";

			return false;
		}
		else
		{
			return true;
		}
	}
};

