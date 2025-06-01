#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

//#include "Global.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:\n";
		cout << "\n________________________\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n________________________\n";
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		float Amount;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadFloatNumebr();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another one? ";
			Amount = clsInputValidate::ReadFloatNumebr();
		}
		return Amount;
	}

	static string _ReadAccountNumber(string FromTo = "From")
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number to Transfer " << FromTo << ":  ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Numebr in Not found, Please Enter Another One! ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t    Transfer Screen");

		clsBankClient SoruceClient = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientCard(SoruceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));

		while (SoruceClient.AccountNumber() == DestinationClient.AccountNumber())
		{
			cout << "\nYou can't Transfer Money to yourself\n";
			DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));
		}

		_PrintClientCard(DestinationClient);

		float Amount = _ReadAmount(SoruceClient);

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation? y/n ? ";
		cin >> ws >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (SoruceClient.Transfer(Amount, DestinationClient , CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer is Failed\n";
			}
		}
		else
		{
			cout << "\nTransfer is Cancelled\n";
		}
		
		_PrintClientCard(SoruceClient);

		_PrintClientCard(DestinationClient);
	}
};

