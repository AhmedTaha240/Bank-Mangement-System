#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" 
            << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(40) << Client.FullName();
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }

public:
    static void ShowTotalBalancesScreen()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientList();

        string Title = "\t Balances List Screen" ;
        string SubTitle = "\t    (" + to_string(vClients.size()) + ")" + " Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n\t\t____________________________________________________"
            "___________________________________________\n\n";

        cout << setw(25) << left << "" 
            << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
         
        cout << "\n\t\t____________________________________________________"
            "___________________________________________\n\n";

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Avaliable In the system!";
        }
        else
        {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordBalanceLine(C);
                cout << endl;
            }
        }
         
        cout << "\n\t\t____________________________________________________"
            "___________________________________________\n";

        cout << "\n\t\t\t\t\t\t\t   Total Balances = " << TotalBalances << endl;

        cout << setw(8) << left << "" 
            << "\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")" << endl;
    }
};

