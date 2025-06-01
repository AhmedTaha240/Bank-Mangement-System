#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "clsString.h" 
#include "clsPerson.h" 

using namespace std;

class clsBankClient : public clsPerson
{

private:
	enum  enMode {EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkToDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1],
			vClientData[2], vClientData[3], vClientData[4],vClientData[5], stof(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode,"", "", "", "", "", "", 0);
	}

	///////// Update Client Data
	static vector <clsBankClient> _LoadClientsObejctFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile , Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	string _ConverClientObjectToLine(clsBankClient Client , string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);   // write Mode

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsBankClient& C : vClients)
			{
				if (C._MarkToDelete == false)
				{
					// we only write records that are not marked for delete
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void Update()
	{
		vector <clsBankClient> _vClients = _LoadClientsObejctFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;

				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	///////// Add New Client 
	void _AddDataLineToFile(string stDateLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app | ios::out);   // append Mode

		if (MyFile.is_open())
		{
			MyFile << stDateLine << endl;

			MyFile.close();
		}
	}

	void AddNew()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	// Extention 07 - Create Transfer Log
	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string Line = "";

		Line += clsDate::GetSystemDateTimeString() + Seperator;
		Line += AccountNumber() + Seperator;
		Line += DestinationClient.AccountNumber() + Seperator;

		Line += to_string(Amount) + Seperator;
		Line += to_string(AccountBalance) + Seperator;
		Line += to_string(DestinationClient.AccountBalance) + Seperator;
		
		Line += UserName;

		return Line;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient ,string UserName )
	{
		string Line = _PrepareTransferLogRecord(Amount, DestinationClient , UserName);
		
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	// Extention 08 - Show Transfers Log Screen
	struct stTransferLogRecord ;

	static stTransferLogRecord _ConvertLineToTransferRecord(string Line, string Delim = "#//#")
	{
		vector <string> vTransferRecords = clsString::Split(Line, Delim);

		stTransferLogRecord TransferLogRecord;

		TransferLogRecord.DateTime = vTransferRecords[0];
		TransferLogRecord.SourceAccount = vTransferRecords[1];
		TransferLogRecord.DestinationAccount = vTransferRecords[2];
		TransferLogRecord.Amount = stof( vTransferRecords[3]);
		TransferLogRecord.SourceBalance = stof(vTransferRecords[4]);
		TransferLogRecord.DestinationBalance = stof(vTransferRecords[5]);
		TransferLogRecord.UserName = vTransferRecords[6];

		return TransferLogRecord;
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	//Read only property  
	string AccountNumber()
	{
		return _AccountNumber;
	}

	// property Set
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	// property Get
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	
	// property Set
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	// property Get
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	///////// Find Client Data
	static clsBankClient Find(string AccountNumebr)
	{
		//vector < clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumebr)
				// can't access to private data member _AccountNumber
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumebr, string PinCode)
	{
		//vector < clsBankClient> vClients;   // Not Important

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumebr && Client.PinCode == PinCode )
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	// No UI Related code inside object
	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}*/

	///////// Update & Add Client Data  
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
		}

		case enMode::UpdateMode:
		{
			Update();

			return enSaveResults::svSucceeded;
		}

		case enMode::AddNewMode:
		{
			// This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				AddNew();

				// We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	///////// Add New Client 
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	///////// Delete Client 
	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsObejctFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkToDelete = true;
				break;
			}
		}
	
		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	///////// List Clients
	static vector <clsBankClient> GetClientList()
	{
		return _LoadClientsObejctFromFile();
	}

	///////// Total Balances
	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientList();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	///////// Deposit
	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	///////// Withdraw
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	///////// Extension 06 - Teransfer 
	bool Transfer(float Amount, clsBankClient& DestinationClient , string UserName)
	{
		if (!Withdraw(Amount))
		{
			return false;
		}
		//this->Withdraw(Amount);
				// or
		/*Withdraw(Amount)*/

		DestinationClient.Deposit(Amount);

		// Extention 07 - Create Transfer Log
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		
		return true;
	}

	// Extention 08 - Show Transfers Log Screen
	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccount;
		string DestinationAccount;
		float Amount;
		float SourceBalance;
		float DestinationBalance;
		string UserName;
	};

	static vector < stTransferLogRecord> GetTransferLogList()
	{
		vector < stTransferLogRecord> vTransferLogRecords;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);  // read Mode

		if (MyFile.is_open())
		{
			string Line;

			stTransferLogRecord TransferRecord;

			while (getline(MyFile , Line))
			{
				TransferRecord = _ConvertLineToTransferRecord(Line);

				vTransferLogRecords.push_back(TransferRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecords;
	}
	
};

