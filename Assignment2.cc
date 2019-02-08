// 2nd assignment.cpp : Defines the entry point for the console application.
// We have dataset containing pairs of DateSpec and Event. Event is simple
/* string describing happening. DateSpec species when this event will take
place. It consists four elds: Day, Month, Year and Weekday. Each eld can
specify exact value or wildcard value.
Possible values are:
Year: 1754 .. 99991, or 0 for any.
Month: 1..12 or 0 for any.
Day: 1..LAST2, 0 for any or -1 for LAST.
Weekday: 1..7 for days from Monday to Sunday or 0 for any.
Task
Create program to tell happenings on seven days starting from given date.
korppi>Assignment2
Date? 28 2 2016
28. 2.2016 [Sun] -
29. 2.2016 [Mon] Payday
1. 3.2016 [Tue] Birthday Party
2. 3.2016 [Wed] -
3. 3.2016 [Thu] -
4. 3.2016 [Fri] Darts Evening
5. 3.2016 [Sat] -
korppi>
This could base on dataset like
1We have selected arbitrary upper limit for year, in principle we could go to eternity,
but that wouldn't be practical.
2LAST is appropriate number betweem 31..28 depending on month and year.
1
EventSpec MyHappenings[] =
{
{ -1, 0, 0, 0, "Payday" }, // Last day of month is payday
{ 1, 3, 0, 0, "Birthday Party" }, // Birthday at 1.3
{ 0, 0, 0, 5, "Darts evening" }, // Darts on Fridays
{13, 0, 0, 5, "Friday the 13th" },
};
Any combination of wildcards should work. Multiple happenings for same
day are given on same line separated by commas.
Notes
Remember to handle special cases (change of month, change of year, leapyears,
...) correctly. Program should be able to handle any date after Tuesday
1.1.1754 (start of Gregorian calendar in Finland).
Weekday can be determined by counting days from day zero (1.1.1754
here) and using modulo 7 appropriate way.
Program should be created as C++ source code and compiled using
tutg++. */

#include<iostream>
#include<string>
#include <ctime>
using namespace std;


struct Date
{
	int day;
	int month;
	int year;
};

Date calendar[7] = {};

int day;
int month;
int year;

int lastday;
struct EventSpec
{
	int day;
	int month;
	int year;
	int weekdays;
	string event;
};

EventSpec MyHappenings[] =
{
	{ -1, 0, 0, 0, "Payday" }, // Last day of month is payday
	{ 1, 3, 0, 0, "Birthday Party" }, // Birthday at 1.3
	{ 0, 0, 0, 5, "Darts evening" }, // Darts on Fridays
	{ 13, 0, 0, 5, "Friday the 13th" },
};

bool inputvalidation()
{
	bool datevalid=true;
	
	if (day < 1 || day>31 || month < 1 || month>12 || year < 1754)
	{
		datevalid=false;
	}
	return datevalid;
}

void errormessage()
{
	if (inputvalidation()==false)
	{
		cout << "Please enter a valid Date" << endl;
	}
}

void input()
{
	
	f : cout << "Please enter the day:" << endl;
	cin >> day;
	cout << "Please enter the month:" << endl;
	cin >> month;
	cout << "Please enter the year:" << endl;
	cin >> year;
	if (inputvalidation())
	{
		calendar[0].day = day;
		calendar[0].month = month;
		calendar[0].year = year;
	}
	else
	{
		errormessage();
		goto f;
	}
}



void increment()
{

	if (calendar[0].month == 1 || calendar[0].month == 3 || calendar[0].month == 5 || calendar[0].month == 7 || calendar[0].month == 8 || calendar[0].month == 10 || calendar[0].month == 12)
	{
		lastday = 31;
		for (int i = 1; i <= 6; i += 1)
		{

			if (calendar[i - 1].day == 31)
			{
				calendar[i].day = 1;
				calendar[i].month = calendar[i - 1].month + 1;

			}
			else if (calendar[i - 1].day>31)
			{
				calendar[i].day = calendar[i - 1].day - 1;
				calendar[i].month = calendar[i - 1].month + 1;

			}
			else
			{

				calendar[i].day = calendar[i - 1].day + 1;
				calendar[i].month = calendar[i - 1].month;

			}
			calendar[i].year = calendar[0].year;
		}

	}
	else if (calendar[0].month == 4 || calendar[0].month == 6 || calendar[0].month == 9 || calendar[0].month == 11)
	{
		lastday = 30;
		for (int i = 1; i <= 6; i += 1)
		{
			if (calendar[i - 1].day == 29)
			{
				calendar[i].day = calendar[i - 1].day + 1;
				calendar[i].month = calendar[i - 1].month;
			}
			else if (calendar[i - 1].day == 30)
			{
				calendar[i].day = 1;
				calendar[i].month = calendar[i - 1].month + 1;
			}
			else if (calendar[i - 1].day>30)
			{
				calendar[i].day = calendar[i - 1].day - 1;
				calendar[i].month = calendar[i - 1].day + 1;
			}
			else
			{
				calendar[i].day = calendar[i - 1].day + 1;
				calendar[i].month = calendar[i - 1].month;
			}
			calendar[i].year = calendar[0].year;
		}

	}

	else if (calendar[0].month == 12)
	{
		lastday = 31;
		for (int i = 1; i <= 6; i += 1)
		{
			if (calendar[i - 1].day == 31)
			{
				calendar[i].day = 1;
				calendar[i].month = 1;
				calendar[i].year = calendar[i - 1].year + 1;
			}
			else
			{
				calendar[i].day = calendar[i - 1].day + 1;
				//calendar[i].month = calendar[i - 1].month;
			}
			calendar[i].month = calendar[0].month;
			calendar[i].year = calendar[0].year;
		}

	}
	else if ((calendar[0].year % 400 == 0 || calendar[0].year % 100 != 0) && calendar[0].year % 4 == 0 && calendar[0].month == 2)
	{
		for (int i = 1; i <= 6; i += 1)
		{
			if (calendar[i - 1].day == 29)
			{
				calendar[i].day = 1;
				calendar[i].month = 3;
			}
			else
			{
				calendar[i].day = calendar[i - 1].day + 1;
				calendar[i].month = calendar[i - 1].month;
			}
			
			calendar[i].year = calendar[0].year;
		}
	}

}

int dayofweek(int d, int m, int y){
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

void output()
{
	string event[7];
	cout<< "Date? " << calendar[0].day << " " << calendar[0].month << " " << calendar[0].year << endl;
	increment();
	string weekday[7];
	
	for (int i = 0; i < 7; i++)
	{
		//for (int j = 0; j < 7; j++)
		//{
			
			switch (dayofweek(calendar[i].day,calendar[i].month,calendar[i].year))
			{
				case 1:
					weekday[i] = "Mon";
					break;
				case 2:
					weekday[i] = "Tue";
					break;
				case 3:
					weekday[i] = "Wed";
					break;
				case 4:
					weekday[i] = "Thu";
					break;
				case 5:
					weekday[i] = "Fri";
					break;
				case 6:
					weekday[i] = "Sat";
					break;
				case 7:
					weekday[i] = "Sun";
					break;
			}
			if (calendar[i].day <= 31 && calendar[i].day >= 28)
			{
				if ((calendar[i].month == 1 || calendar[i].month == 3 || calendar[i].month == 5 || calendar[i].month == 7 || calendar[i].month == 8 || calendar[i].month == 10 || calendar[i].month == 12) && calendar[i].day==31)
				{
					event[i] = MyHappenings[0].event;
				}
				else if (calendar[i].month == 4 || calendar[i].month == 6 || calendar[i].month == 9 || calendar[i].month == 11 && calendar[i].day==30)
				{
					event[i] = MyHappenings[0].event;
				}
				else if (calendar[i].month == 2 && calendar[i].day==29)
				{
					event[i] = MyHappenings[0].event;
				}
				else
				{
					event[i] = "-";
				}
			}
			else if (calendar[i].day == 1 && calendar[i].month == 3)
			{
				event[i] = MyHappenings[1].event;
			}
			else if (calendar[i].day == 13 && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)
			{
				event[i] = MyHappenings[3].event;
			}
			else if (dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)
			{
				event[i] = MyHappenings[2].event;
			}
			else
			{
				event[i] = "-";
			}
		//}
		
	}


	for (int i = 0; i <= 6; i += 1)
	{
		cout << calendar[i].day << "." << calendar[i].month << "." << calendar[i].year << " " <<"["<< weekday[i]<<"]" <<" "<< event[i] << endl;
		//cout << calendar[0].day << "." << calendar[0].month << "." << calendar[0].year <<" "<<event[0]<< endl;
		/*cout << calendar[1].day << "." << calendar[1].month << "." << calendar[1].year << " " << event[1] << endl;
		cout << calendar[2].day << "." << calendar[2].month << "." << calendar[2].year << " " << event[2]<< endl;
		cout << calendar[3].day << "." << calendar[3].month << "." << calendar[3].year << " " << event[3]<< endl;
		cout << calendar[4].day << "." << calendar[4].month << "." << calendar[4].year << " " << event[4]<< endl;
		cout << calendar[5].day << "." << calendar[5].month << "." << calendar[5].year << " " << event[5] << endl;
		cout << calendar[6].day << "." << calendar[6].month << "." << calendar[6].year << " " << event[6] << endl;*/
	}
}



void main()
{
	input();
	if (calendar[0].day!=0)
	{
		output();
	}
	
	string buffer;
	cin >> buffer;
	/*cout << calendar[0].day << "." << calendar[0].month << "." << calendar[0].year << " " << event << endl;
	cout << calendar[1].day << "." << calendar[1].month << "." << calendar[1].year << " " << event << endl;
	cout << calendar[2].day << "." << calendar[2].month << "." << calendar[2].year << " " << event << endl;
	cout << calendar[3].day << "." << calendar[3].month << "." << calendar[3].year << " " << event << endl;
	cout << calendar[4].day << "." << calendar[4].month << "." << calendar[4].year << " " << event << endl;
	cout << calendar[5].day << "." << calendar[5].month << "." << calendar[5].year << " " << event << endl;
	cout << calendar[6].day << "." << calendar[6].month << "." << calendar[6].year << " " << event << endl;*/
}