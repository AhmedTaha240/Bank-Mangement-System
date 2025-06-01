#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Day = 1, _Month = 1, _Year = 1900;

public:
	//clsDateInfo Date1;
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string Date)
	{
		vector <string> vDate;

		vDate = clsString::Split(Date, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DateOrderInYear, short Year)
	{
		clsDate Date1 = GetDateFromOrderInYear(DateOrderInYear, Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate()
	{
		//system date
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		
		short Day, Month, Year,Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return to_string(Day)+ "/" + to_string(Month) + "/" +
			to_string(Year) + " - " + to_string(Hour) + ":"
			+ to_string(Minute) + ":" + to_string(Second) ;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static bool isLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;

		int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2 ? isLeapYear(Year) ? 29 : 28 : arrDays[Month - 1]);
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return  NumberOfDaysInAMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth()
	{
		return  NumberOfDaysInAMonth(_Month, _Year) * 24;
	}

	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return  NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth()
	{
		return  NumberOfHoursInAMonth(_Month, _Year) * 60;
	}

	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return  NumberOfMinutesInAMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInAMonth()
	{
		return  NumberOfMinutesInAMonth(_Month, _Year) * 60;
	}

	static short NumberOfDaysInAYear(short Year)
	{
		return  isLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInAYear()
	{
		return  NumberOfDaysInAYear(_Year);
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return  NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return  NumberOfHoursInAYear(_Year);
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return  NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return  NumberOfMinutesInAYear(_Year);
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return  NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return  NumberOfSecondsInAYear(_Year);
	}

	static clsDate GetDateFromOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;

		short RemainingDays = DayOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (short i = 1; i < Month; i++)
		{
			TotalDays += NumberOfDaysInAMonth(Month, Year);
		}
		TotalDays += Day;

		return TotalDays;
	}
	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;

		short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
		return d;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static string DayName(short NumberOfDay)
	{
		string arrDay[7] = { "Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat" };

		return arrDay[NumberOfDay];
	}
	static string MonthName(short NumebrOfMonth)
	{
		string arrMonth[12] = { "Jan" , "Feb" , "Mar" , "Apr" , "May" ,
			   "Jun" , "Jul" , "Aug" , "Sep" , "Oct" , "Nov" , "Dec" };

		return arrMonth[NumebrOfMonth - 1];
	}
	string MonthName()
	{
		return MonthName(_Month);
	}
	static void PrintMonthCalender(short Month, short Year)
	{
		short NumberOfDays = NumberOfDaysInAMonth(Month, Year);

		// Index of the day from 0 to 6
		short DayOrder = DayOfWeekOrder(1, Month, Year);

		string month = MonthName(Month);

		// Print the current month name
		cout << "\n_________________" << month << "_____________________\n";

		// Print the columns
		cout << "\n  Sun  Mon  Tue  Wed  Thur  Fri  Sat\n";

		// Print appropriate spaces
		int i;
		for (i = 0; i < DayOrder; i++)
		{
			cout << "     ";
		}
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				cout << "\n";
			}
		}
		cout << "\n_________________________________________\n";
	}

	void PrintMonthCalender()
	{
		PrintMonthCalender(this->Month, this->Year);
	}

	static void PrintYearCalender(short Year)
	{
		cout << "\n_______________________________________\n\n";
		printf("         Calendar - %d \n", Year);
		cout << "_______________________________________\n\n";


		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalender(i, Year);
		}

		cout << "\n_________________________________________\n";
	}

	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}

	static clsDate DateAddDays(short Days, clsDate Date)
	{
		short RemainingDays = Days +
			NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);

		short MonthDays = 0;
		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	clsDate DateAddDays(short Days)
	{
		return DateAddDays(Days, *this);
	}

	static bool isDateBeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true :
			(Date1.Year == Date2.Year) ?
			(Date1.Month < Date2.Month) ? true :
			((Date1.Month == Date2.Month) ?
				Date1.Day < Date2.Day : false) : false;
	}

	bool isDateBeforeDate2(clsDate Date2)
	{
		return isDateBeforeDate2(*this, Date2);
	}

	static bool isDateEqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) ?
			(Date1.Month == Date2.Month) ?
			(Date1.Day == Date2.Day) : true : false;
	}

	bool isDateEqualDate2(clsDate Date2)
	{
		return isDateEqualDate2(*this, Date2);
	}

	static bool isDateAfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!isDateBeforeDate2(Date1, Date2) && !isDateEqualDate2(Date1, Date2));
	}

	bool isDateAfterDate2(clsDate Date2)
	{
		return isDateAfterDate2(*this, Date2);
	}

	static bool isLastDayInAMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
	}

	bool isLastDayInAMonth()
	{
		return isLastDayInAMonth(*this);
	}

	static bool isLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool isLastMonthInYear()
	{
		return isLastMonthInYear(this->Month);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (isLastDayInAMonth(Date))
		{
			if (isLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (isLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		//last check day in date should not exceed max days in the current month
		// example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should be 28/2/2022

		short NumebrOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumebrOfDaysInCurrentMonth)
		{
			Date.Day = NumebrOfDaysInCurrentMonth;
		}
		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(short Months, clsDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;

		// this is my check of day 
		short NumebrOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumebrOfDaysInCurrentMonth)
		{
			Date.Day = NumebrOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(Years, *this);
	}

	static clsDate IncreaseDateByXYearsFaster(short Years, clsDate Date)
	{
		Date.Year += Years;

		// this is my check of day 
		short NumebrOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumebrOfDaysInCurrentMonth)
		{
			Date.Day = NumebrOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByXYearsFaster(short Years)
	{
		IncreaseDateByXYearsFaster(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		// Period of 10 years
		Date.Year += 10;

		// this is my check of day 
		short NumebrOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumebrOfDaysInCurrentMonth)
		{
			Date.Day = NumebrOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(short Decade, clsDate Date)
	{
		for (short i = 1; i <= Decade * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByXDecades(short Decade)
	{
		IncreaseDateByXDecades(Decade, *this);
	}

	static clsDate IncreaseDateByXDecadesFaster(short Decade, clsDate Date)
	{
		Date.Year += Decade * 10;

		// this is my check of day 
		short NumebrOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumebrOfDaysInCurrentMonth)
		{
			Date.Day = NumebrOfDaysInCurrentMonth;
		}

		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decade)
	{
		IncreaseDateByXDecadesFaster(Decade, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		//Period of 100 years
		Date.Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		//Period of 1000 years
		Date.Year += 1000;
		return Date;
	}


	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Year--;
			Date.Month = 12;
		}
		else
		{
			Date.Month--;
		}

		// last check in date should not exceed max days in the current month.   

		// example if date is 31/3/2022 decreasing one month should not be   
		//31 / 2 / 2022, it should be 28 / 2 / 2022
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}
		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;

		// the professour didn't write this step in his solution 
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByXYearsFaster(short Years, clsDate Date)
	{
		Date.Year -= Years;

		// the professour didn't write this step in his solution 
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}
		return Date;
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		//Period of 10 years
		Date.Year -= 10;

		// the professour didn't write this step in his solution 
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate Date)
	{
		for (short i = 1; i <= Decades * 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate Date)
	{
		Date.Year -= Decades * 10;

		// the professour didn't write this step in his solution 
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}
		return Date;
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		//Period of 100 years
		Date.Year -= 100;

		// the professour didn't write this step in his solution 
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}

		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		//Period of 1000 years
		Date.Year -= 1000;

		// the professour didn't write this step in his solution 
		short NumberOfCurrentDays = NumberOfDaysInAMonth(Date.Month,
			Date.Year);
		if (Date.Day > NumberOfCurrentDays)
		{
			Date.Day = NumberOfCurrentDays;
		}

		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date) == 6);
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(clsDate Date)
	{
		return (DayOfWeekOrder(Date) == 5 || DayOfWeekOrder(Date) == 6);
	}

	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return (!IsWeekend(Date));
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!isDateBeforeDate2(Date1, Date2))
		{
			SwapFlagValue = -1;
			SwapDates(Date1, Date2);
		}

		while (isDateBeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return (IncludeEndDay) ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilTheEndOfWeek()
	{
		return  DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date1)
	{

		clsDate EndOfMontDate;
		EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
		EndOfMontDate.Month = Date1.Month;
		EndOfMontDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfMontDate, true);

	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date1)
	{

		clsDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date1.Year;

		return GetDifferenceInDays(Date1, EndOfYearDate, true);

	}

	short DaysUntilTheEndOfYear()
	{
		return  DaysUntilTheEndOfYear(*this);
	}

	//i added this method to calculate business days between 2 days
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{

		short Days = 0;
		while (isDateBeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}

		return Days;

	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		/*short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				Days++;

			DateFrom = AddOneDay(DateFrom);
		}*/

		return CalculateBusinessDays(DateFrom, DateTo);

	}
	//above method is eough , no need to have method for the object

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		for (short i = 1; i <= VacationDays; i++)
		{
			if (IsWeekend(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}
		//to add weekends 
		for (short i = 1; i <= WeekEndCounter; i++)
			DateFrom = AddOneDay(DateFrom);

		return DateFrom;
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (isDateBeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (isDateEqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		/* if (IsDate1AfterDate2(Date1,Date2))
			 return enDateCompare::After;*/

			 //this is faster
		return enDateCompare::After;

	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static int CalculateMyAgeInDays(clsDate Date1)
	{
		clsDate Date2;
		int Days = 0;

		Days = GetDifferenceInDays(Date1, Date2);

		return Days;
	}

	static bool isValidDate(clsDate Date)
	{
		short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth || Date.Year <= 0)
			return false;

		return true;
	}

	bool isValidDate()
	{
		return isValidDate(*this);
	}

	static string FormatString(clsDate Date, string Format = "dd/mm/yyyy")
	{
		Format.replace(Format.find("dd"), 2, to_string(Date.Day));
		Format.replace(Format.find("mm"), 2, to_string(Date.Month));
		Format.replace(Format.find("yyyy"), 4, to_string(Date.Year));
		return Format;
	}

	string FormatString(string Format = "dd/mm/yyyy")
	{
		return FormatString(*this, Format);
	}
};



