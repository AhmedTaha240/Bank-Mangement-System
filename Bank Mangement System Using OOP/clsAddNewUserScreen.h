#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
        cout << "\nEnter FirstName : ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName  : ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email     : ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone     : ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password  : ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
	}

    static void _PrintUserInfo(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";
    }

    static short _ReadPermissionsToSet()
    {
        char Answer = 'n';
        short Permissions = 0;

        cout << "\n\nDo you want to give full access? y/n?  ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            return clsUser::enPermissions::pAll;
        }

        cout << "\n\nDo you want to give access to : \n";
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
             Permissions += clsUser::enPermissions::pListClient;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
             Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
             Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
             Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
             Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
             Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nLogin Regiseter? y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }
     /*   if (Permissions == 127)
        {
            return clsUser::enPermissions::pAll;
        }*/

        return Permissions;
    }

public:

    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\t   Add New User Screen");

        string UserName = "";
        cout << "Please Enter Username:  ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExists(UserName))
        {
            cout << "\nThis UserName is already exists, choose anthor one  ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(User);

        clsUser::enSaveResults SaveResult;

        SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsUser::svFailedEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;
        }
        case clsUser::svSucceeded:
        {
            cout << "\nUser Added Successfully :-)\n";
            _PrintUserInfo(User);
            break;
        }
        case clsUser::svFailedUserExists:
        {
            cout << "\nError User was not saved because it's used!\n";
            break;
        }
        }
    }
};

