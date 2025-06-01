#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "clsString.h" 
#include "clsPerson.h" 
#include "clsDate.h" 

#include "clsUtil.h" 

using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode {EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode;
	string _UserName;
	string _Password;
	short _Permissions;
	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector <string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToDataLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		// here we encrypt store the encrypted password not the real one.
		UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;
	}

	///////// Update User Data
	static vector <clsUser> _LoadUserDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);   // write Mode

		if (MyFile.is_open())
		{
			string DataLine;
			for (clsUser& U : vUsers)
			{
				if (U._MarkForDelete == false)
				{
					//we only write records that are not marked for delete. 
					DataLine = _ConvertUserObjectToDataLine(U);

					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> vUsers = _LoadUserDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				//we only write records that are not marked for delete. 
				U = *this;

				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	///////// Add New User Data
	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::app | ios::out);   // append Mode

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew()
	{
		return (_AddDataLineToFile(_ConvertUserObjectToDataLine(*this)));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	///////// Register Logins In a Log File 
	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += (clsDate::GetSystemDateTimeString()) + Seperator;

		LoginRecord += UserName + Seperator;
		//here we encypt store the encrypted Password not the real one.
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	// Show Login Register Screen
	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Delim = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line, Delim);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

public:
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int Permissions):
		clsPerson(FirstName,LastName,Email,Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions {pAll = -1 , pListClient = 1 , pAddNewClient = 2, pDeleteClient = 4,
					pUpdateClients = 8, pFindClient = 16, pTransactions = 32 ,
					pManageUsers = 64 , pLoginRegister = 128
	};

	// property Set
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	// property Get
	string GetUserName()
	{
		return _UserName ;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	// property Set
	void SetPassword(string Password)
	{
		_Password = Password;
	}

	// property Get
	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	// property Set
	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	// property Get
	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkForDelete()
	{
		return _MarkForDelete;
	}

	///////// Find User Data
	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (clsString::LowerAllString(User.UserName) == clsString::LowerAllString(UserName))
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName , string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	enum enSaveResults {svFailedEmptyObject = 0 , svSucceeded = 1 , svFailedUserExists = 2};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::enMode::EmptyMode:
		{
			return enSaveResults::svFailedEmptyObject;
		}

		case clsUser::enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::svSucceeded;
		}
		case clsUser::enMode::AddNewMode:
		{
			if (clsUser::IsUserExists(_UserName))
			{
				return enSaveResults::svFailedUserExists;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	static bool IsUserExists(string UserName)
	{
		clsUser User =  clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	///////// Add New User 
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return (_LoadUserDataFromFile());
	}

	///////// Delete User 
	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUserDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	///////// Check Permissions of User 
	
	// You can't do this because this clsUser is called in Global.h so this cause Circular Dependency
	/*static bool ChekcAccessPermission(enPermissions Permissions)
	{
		if (CurrentUser.Permissions == enPermissions::pAll)
			return true;

		//CurrentUser = Find(UserName, Password);

		if ((CurrentUser.Permissions & Permissions) == Permissions)
		{
			return true;
		}
		else
		{
			return false;
		}
	}*/

	bool ChekcAccessPermission(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::pAll)
			return true;

	/*	if ((this->Permissions & Permissions) == Permissions)
		{
			return true;
		}
		else
		{
			return false;
		}*/

		return ((this->Permissions & Permissions) == Permissions) ? true : false;
	}

	///////// Register Logins In a Log File 
	void RegisterLogIn()
	{
		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::app | ios::out);  // append Mode

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			
			MyFile.close();
		}
	}

	// Show Login Register Screen
	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		short Permissions;
	};

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecords;
		string Line;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			stLoginRegisterRecord LoginRegisterRecord; 

			while (getline(MyFile , Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				
				vLoginRegisterRecords.push_back(LoginRegisterRecord);
			}
			MyFile.close();
		}
		return vLoginRegisterRecords;
	}


};

