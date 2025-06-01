#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
	enum enMode {EmptyMode = 0 , UpdateMode = 1};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Delim = "#//#")
	{
		vector <string> vCurrency;
		vCurrency = clsString::Split(Line, Delim);

		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1],
			vCurrency[2], stof(vCurrency[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency ,string Seperator = "#//#")
	{
		string CurrencyRecord = "";

		CurrencyRecord += Currency._Country + Seperator;
		CurrencyRecord += Currency._CurrencyCode + Seperator;
		CurrencyRecord += Currency._CurrencyName + Seperator;
		CurrencyRecord += to_string(Currency._Rate);

		return CurrencyRecord;
	}

	static vector < clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector < clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);   // read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				vCurrency.push_back(Currency);
			}
			MyFile.close();
		}

		return vCurrency;
	}

	static void _SaveCurrencyDataToFile(vector < clsCurrency> vCurrency)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);   // overwrite Mode

		if (MyFile.is_open())
		{
			string Line;
			for (clsCurrency& C : vCurrency)
			{
				Line = _ConvertCurrencyObjectToLine(C);

				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector < clsCurrency> vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : vCurrency)
		{
			if (C.CurrencyCode() == _CurrencyCode )
			{
				C._Rate = _Rate;
				//break;
			}
		}

		_SaveCurrencyDataToFile(vCurrency);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode,
		string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	// read only  (get Country)
	string Country()
	{
		return _Country;
	}

	// read only  (get CurrencyCode)
	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	// read only  (get CurrencyName)
	string CurrencyName()
	{
		return _CurrencyName;
	}

	// set Rate Exchange
	void UpdateRate(float NewRate)
	{
		if (this->IsEmpty())
			return;

		_Rate = NewRate;
		_Update();
	}

	// get Rate Exchange
	float Rate()
	{
		return _Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);  // read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();

					return Currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);  // read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExists(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector < clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	// Currency Exchange
	float ConvertToUSD(float Amount)
	{
		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return AmountInUSD * Currency2.Rate();
	}
};

