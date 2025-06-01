#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

#include <sstream>

using namespace std;

class clsInputValidate
{
public:
	static bool IsNumebrBetween(short Number, short From, short To)
	{
		if (From > To)
		{
			short Temp;
			Temp = From;
			From = To;
			To = Temp;
		}
		return (Number >= From && Number <= To);
	}

	static bool IsNumebrBetween(int Number, int From, int To)
	{
		if (From > To)
		{
			int Temp;
			Temp = From;
			From = To;
			To = Temp;
		}
		return (Number >= From && Number <= To);
	}

	static bool IsNumebrBetween(float Number, float From, float To)
	{
		if (From > To)
		{
			float Temp;
			Temp = From;
			From = To;
			To = Temp;
		}
		return (Number >= From && Number <= To);
	}

	static bool IsNumebrBetween(double Number, double From, double To)
	{
		if (From > To)
		{
			double Temp;
			Temp = From;
			From = To;
			To = Temp;
		}
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		/*if (DateFrom.clsDate::isDateAfterDate2(DateTo))
		{
			clsDate::SwapDates(DateFrom, DateTo);
		}*/

		// Date >= From && Date <= To
		if ((clsDate::isDateAfterDate2(Date, From) || clsDate::isDateEqualDate2(Date, From))
			&& (clsDate::isDateBeforeDate2(Date, To) || clsDate::isDateEqualDate2(Date, To))
			)
		{
			return true;
		}

		// Date >= To && Date <= From
		if ((clsDate::isDateAfterDate2(Date, To) || clsDate::isDateEqualDate2(Date, To))
			&& (clsDate::isDateBeforeDate2(Date, From) || clsDate::isDateEqualDate2(Date, From))
			)
		{
			return true;
		}

		return false;
	}

	static int ReadIntNumebr(string ErrorMessage = "Invalid Numebr, Enter again\n")
	{
		int Number;

	/*	while (!(cin >> Number))
		{
			cin.clear();
			cout << ErrorMessage;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		return Number;*/
							// or
		string Input;
		while (true)
		{
			// reads the entire input line into the input string.
			getline(cin >> ws, Input);

			// creates a stringstream object ss initialized with the input string.
			stringstream ss(Input);

			// extracts the integer value from the stringstream.
			//ss.eof() checks if the stringstream has reached the end - of - file
			//  after the integer extraction.If there are extra characters,
			//  it means the input is invalid.
			if (ss >> Number && ss.eof())
				return Number;
			else
				cout << "\nError validation, Enter again:  ";
		}
	}

	static int ReadIntNumebrBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int Number = ReadIntNumebr();

		while (!IsNumebrBetween(Number , From , To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumebr();
		};

		return Number;
	}

	static double ReadDblNumebr(string ErrorMessage = "Invalid Numebr, Enter again\n" )
	{
		double Number;

	/*	while (!(cin >> Number))
		{
			cin.clear();
			cout << ErrorMessage ;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		return Number;*/

						// or

		string Input;
		while (true)
		{
			// reads the entire input line into the input string.
			getline(cin >> ws, Input);

			// creates a stringstream object ss initialized with the input string.
			stringstream ss(Input);

			// extracts the integer value from the stringstream.
			//ss.eof() checks if the stringstream has reached the end - of - file
			//  after the integer extraction.If there are extra characters,
			//  it means the input is invalid.
			if (ss >> Number && ss.eof())
				return Number;
			else
				cout << "\nError validation, Enter again:  ";
		}
	}

	static double ReadDblPositiveNumebr(string ErrorMessage = "Invalid Numebr, Enter again\n")
	{
		double Number;

		/*	while (!(cin >> Number))
			{
				cin.clear();
				cout << ErrorMessage ;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			return Number;*/

			// or

		string Input;
		while (true)
		{
			// reads the entire input line into the input string.
			getline(cin >> ws, Input);

			// creates a stringstream object ss initialized with the input string.
			stringstream ss(Input);

			// extracts the integer value from the stringstream.
			//ss.eof() checks if the stringstream has reached the end - of - file
			//  after the integer extraction.If there are extra characters,
			//  it means the input is invalid.
			if (ss >> Number && ss.eof() && Number > 0)
			{
				return Number;
			}
			else
				cout << "\nError validation, Enter again:  ";
		}
	}

	static float ReadFloatNumebr()
	{
		return float(ReadDblPositiveNumebr());
	}

	static double ReadDblNumebrBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double Number = ReadDblNumebr();

		while (!IsNumebrBetween(Number , From , To))
		{
			cout << ErrorMessage;
			Number = ReadDblNumebr();
		};

		return Number;
	}


	static bool IsValidDate(clsDate Date)
	{
		return (Date.clsDate::isValidDate());
	}

	static string ReadString()
	{
		string S1 = "";

		getline(cin >> ws, S1);

		return S1;
	}

	static bool ReadYesOrNo(string Message = "Invalid Answer, [Y / N] ")
	{
		char Answer;
		cin >> Answer;
		
		while (tolower(Answer) != 'y' && tolower(Answer) != 'n')
		{
			cout << "Invalid Choice, ";
			cout << endl << Message;
			cin >> Answer;
		};

		return (tolower(Answer) == 'y' ? true : false);
	}
};



