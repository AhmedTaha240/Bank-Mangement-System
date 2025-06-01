#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord Record)
	{

		cout << setw(8) << left << "" <<
			"| " << setw(25) << Record.DateTime;
		cout << "| " << setw(15) << Record.UserName;
		cout << "| " << setw(15) << Record.Password;
		cout << "| " << setw(15) << Record.Permissions;
	}

public:
	static void ShowLoginRegister()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}

		vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord
			= clsUser::GetLoginRegisterList();

		string Title = "\t   Login Register List Screen";
		string SubTitle = "\t        (" +
			to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t_______________________________________________________"
			"_______________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << setw(25) << "Date/Time";
		cout << "| " << setw(15) << "UserName";
		cout << "| " << setw(15) << "Password";
		cout << "| " << setw(15) << "Permissions";

		cout << "\n\t_______________________________________________________"
			"_______________________________________________\n\n";

		if (vLoginRegisterRecord.size() == 0)
		{
			cout << "\n\t\t\t There is no loigin Register\n";
		}
		else
		{
			for (clsUser::stLoginRegisterRecord& Record : vLoginRegisterRecord)
			{
				_PrintLoginRegisterRecordLine(Record);
				cout << endl;
			}
		}

		cout << "\n\t_______________________________________________________"
			"_______________________________________________\n\n";
	}
};

