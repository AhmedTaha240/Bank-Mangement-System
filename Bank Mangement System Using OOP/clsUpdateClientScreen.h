#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumebr();
    }

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
    static void ShowUpdateClientScreen()
    {
        // you can using ChekcAccessPermission() which is found in clsUser.h
        /* if (!CurrentUser.ChekcAccessPermission(clsUser::enPermissions::pUpdateClients))
        {
            cout << "\nAccess Denied! Contact your Admin\n";
            return;
        }*/
                                            // or
        // you can using a static method CheckAccessRights() which is found in clsScreen.h 
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }

        _DrawScreenHeader("\t Update Client Screen");

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
        cout << "\nAre you sure you want to Update this client y/n?  ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            cout << "\nUpdate Client Info: \n";
            cout << "\n_____________________________________\n";

            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";

                //NewClient.Print();
                _PrintClient(Client1);
                break;
            }
            //case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            //{
            //    cout << "\nError account was not saved because account number is used!\n";
            //    break;
            //}
            }
        }
        else
        {
            cout << "\nUpdate Client is Cancelled.";
        }
    }
};

