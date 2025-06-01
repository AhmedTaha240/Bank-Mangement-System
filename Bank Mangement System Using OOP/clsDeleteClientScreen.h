#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

public:
    static void ShowDeleteClientScreen()
    {
        // you can using ChekcAccessPermission() which is found in clsUser.h
        /* if (!CurrentUser.ChekcAccessPermission(clsUser::enPermissions::pDeleteClient))
         {
            cout << "\nAccess Denied! Contact your Admin\n";
             return;
         }*/
                                        // or
        // you can using a static method CheckAccessRights() which is found in clsScreen.h 
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\t   Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nThis Account Number is Not found, choose anthor one  ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        //Client1.Print();
        _PrintClient(Client1);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client y/n?  ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintClient(Client1);
            }
            else
            {
                cout << "\nError Client Was not Deleted :-(\n";
            }
        }
        else
        {
            cout << "\nDelete Client is Cancelled.\n";
        }
    }
};

