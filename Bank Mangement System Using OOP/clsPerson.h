#pragma once
#include <iostream>
using namespace std;

#include "InterfaceCommunication.h"

class clsPerson : public InterfaceCommunication
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	// property Set
	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	// property Get
	string GetFirstName()
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	// property Set
	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}

	// property Get
	string GetLastName()
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	// property Set
	void SetEmail(string Email)
	{
		_Email = Email;
	}

	// property Get
	string GetEmail()
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	// property Set
	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	// property Get
	string GetPhone()
	{
		return _Phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}

	//InterfaceCommunication Objec1;   // Error :You cannot create an object of InterfaceCommunication
	
	void SendEmail(string Title, string Body)
	{

	}
	
	void SendFax(string Title, string Body)
	{


	}

	void SendSMS(string Title, string Body)
	{


	}
};

