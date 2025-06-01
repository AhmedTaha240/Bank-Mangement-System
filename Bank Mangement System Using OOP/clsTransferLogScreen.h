#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRecord TransferLogRecord)
	{
		cout << setw(8) << left << "" << "| " << setw(25) << TransferLogRecord.DateTime;
		cout << "| " << setw(10) << TransferLogRecord.SourceAccount;
		cout << "| " << setw(10) << TransferLogRecord.DestinationAccount;
		cout << "| " << setw(10) << TransferLogRecord.Amount;
		cout << "| " << setw(15) << TransferLogRecord.SourceBalance;
		cout << "| " << setw(15) << TransferLogRecord.DestinationBalance;
		cout << "| " << setw(15) << TransferLogRecord.UserName;
	}

public:
	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord;

		vTransferLogRecord = clsBankClient::GetTransferLogList();

		string Title = "\t    Transfer Log List Screen";
		string SubTitle = "\t          (" +to_string( vTransferLogRecord.size() )+ ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t____________________________________________________"
			"_____________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(25) << "Date/Time";
		cout << "| " << setw(10) << "s.Acct";
		cout << "| " << setw(10) << "d.Acct";
		cout << "| " << setw(10) << "Amount";
		cout << "| " << setw(15) << "s.Balance";
		cout << "| " << setw(15) << "d.Balance";
		cout << "| " << setw(15) << "User";

		cout << "\n\t____________________________________________________"
			"_____________________________________________________________\n\n";

		if (vTransferLogRecord.size() == 0)
		{
			cout << "\n\t\t\t\t\t No Available Transfer Log Records here\n";
		}
		else
		{
			for (clsBankClient::stTransferLogRecord& Record : vTransferLogRecord)
			{
				_PrintTransferLogRecord(Record);
				cout << endl;
			}
		}

		cout << "\n\t____________________________________________________"
			"_____________________________________________________________\n\n";
	}
};

