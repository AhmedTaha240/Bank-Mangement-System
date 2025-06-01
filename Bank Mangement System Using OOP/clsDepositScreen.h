#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t  Deposit Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with Account Number [" << AccountNumber << "] does Not exists\n";
            cout << "\nPlease Enter Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        //Amount = clsInputValidate::ReadDblNumebr();
        Amount = clsInputValidate::ReadDblPositiveNumebr();

        char Answer = 'n';
        cout << "\nAre you sure you want to perform this transaction? y/n?  ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfully. \n";
            cout << "\nNew Balance Is: " << Client1.AccountBalance;
        }
        else
        {
            cout << "\nOperation was cancelled\n";
        }
    }
};

