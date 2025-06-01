#pragma once
#include <iomanip>
#include "clsBankClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void PrintClientRecordLine(clsBankClient Client)
	{
        cout << setw(8) << left << ""
             << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(20) << Client.Email;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(12) << Client.AccountBalance;

	}

public:

    static void ShowClientsList()
    {
        // you can using ChekcAccessPermission() which is found in clsUser.h
        /* if (!CurrentUser.ChekcAccessPermission(clsUser::enPermissions::pListClient))
         {
            cout << "\nAccess Denied! Contact your Admin\n";
             return;
         }*/
                                        // or
        // you can using a static method CheckAccessRights() which is found in clsScreen.h 
        if (!CheckAccessRights(clsUser::enPermissions::pListClient))
        {
            return;
        }

        vector <clsBankClient> vClients = clsBankClient::GetClientList();

        string Title = "\tClient List Screen";
        string SubTitle = "\n\t\t\t\t\t\t    (" + to_string(vClients.size()) + ") Client(s).";
        clsScreen::_DrawScreenHeader(Title, SubTitle);


        cout << "\n\t_______________________________________________________"
            "_______________________________________________\n\n";

        cout << setw(8) << left << "" << "| " << left 
             << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";

        cout << "\n\t_______________________________________________________"
            "_______________________________________________\n\n";

        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Avaliable In the system!";
        }

        for (clsBankClient& C : vClients)
        {
            PrintClientRecordLine(C);
            cout << endl;
        }
        cout << "\n\t_______________________________________________________"
            "_______________________________________________\n\n";
    }
};

