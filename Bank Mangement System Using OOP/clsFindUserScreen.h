#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t   Find User Screen");

        string UserName = "";
        cout << "Please Enter Username:  ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExists(UserName))
        {
            cout << "\nThis UserName is Not found, choose anthor one  ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);


      /*  if (!User.IsEmpty())    // Not Important because while loop replace it
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-)\n";
        }*/
        _PrintUserInfo(User);
    }
};

