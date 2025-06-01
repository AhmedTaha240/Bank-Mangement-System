#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
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

public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t   Delete User Screen");

        string UserName = "";

        cout << "Please Enter Username:  ";
        UserName = clsInputValidate::ReadString();

        // you can't Delete Admin User:
        if (clsString::LowerAllString(UserName) == "admin")
        {
            cout << "\nSoory you can't delete this user";
            return;
        }

        while (!clsUser::IsUserExists(UserName))
        {
            cout << "\nThis User is Not found, choose anthor one  ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUserInfo(User);

        char Answer;
        cout << "\nAre you sure you want to delete this User? [Y/N]  ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Succeefuuly.\n";
                _PrintUserInfo(User);
            }
            else
            {
                cout << "\nError User Was not Deleted.\n";
            }
        }
        else
        {
            cout << "\nDelete User is Cancelled.";
        }
    }
};

