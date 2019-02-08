// 3nd assignment.cpp : Defines the entry point for the console application.
// 
/* We have dataset containing pairs of DateSpec and Event. Event is simple
string describing happening. DateSpec species when this event will take
place. It consists four elds: Day, Month, Year and Weekday. Each eld can
specify exact value or wildcard value.
Possible values are:
Year: 1754 .. 99991, or 0 for any.
Month: 1..12 or 0 for any.
Day: 1..LAST2, 0 for any or -1 for LAST.
Weekday: 1..7 for days from Monday to Sunday or 0 for any.
Task
Create program to tell happenings on week including given date. Program
should initialize it's dataset from le Events.dat (if present, ask for lename
if isn't).
korppi>Assignment3
Date? 2 3 2016
29. 2.2016 [Mon] Payday
1. 3.2016 [Tue] Birthday Party
2. 3.2016 [Wed] -
3. 3.2016 [Thu] -
4. 3.2016 [Fri] Darts Evening
5. 3.2016 [Sat] -
6. 3.2016 [Sat] -
korppi>
1We have selected arbitrary upper limit for year, in principle we could go to eternity,
but that wouldn't be practical.
2LAST is appropriate number betweem 31..28 depending on month and year.
1
Events.dat contains
# Comment and empty lines are ignored
# '$' means LAST, '*' is wildcard
# Weekday on symbolic from Mon,Tue,Wed,Thu,Fri,Sat,Sun
# Events specs start
# Last day is payday
$.*.*:*:Payday
# Birthday at 1.3
1.3.*:*:Birthday Party
# Darts on Fridays
*.*.*:Fri:Darts evening
13.*.*:Fri:Friday the 13th
# EOF
Any combination of wildcards should work. Multiple happenings for same
day are given on same line separated by commas.
Notes
Remember to handle special cases (change of month, change of year, leapyears,
...) correctly. Program should be able to handle any date after Tuesday
1.1.1754 (start of Gregorian calendar in Finland).
Weekday can be determined by counting days from day zero (1.1.1754
here) and using modulo 7 appropriate way.
Program should be created as C++ source code and compiled using
tutg++.
 */

#include<iostream>
#include<string>
using namespace std;


struct Date
{
	int day;
	int month;
	int year;
};

Date calendar[7] = {};

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

bool inputvalidation(Date &inputdate) // This Function check that if user enter a valid day, month or year
{
	if (inputdate.day < 1 || inputdate.day>31 || inputdate.month < 1 || inputdate.month>12 || inputdate.year < 1754 || inputdate.year>9999)
	{
		return false;
	}
	return true;
}

void errormessage(Date &inputdate) //This Function gives the user an error messege if the entered day, month or year is invalid
{
	if (inputvalidation(inputdate) == false)
	{
		cout << "Please enter a valid Date" << endl;
	}
}

void input(Date &inputdate)// This Function take the input day, month or year from user
{
f: cout << "Please enter the date: (separate day, month and year with space)" << endl;

	cin >> inputdate.day >> inputdate.month >> inputdate.year;


	if (inputvalidation(inputdate))// if the inputdate is valid it will be added to the struct otherwise the program shows an error message to user 
	{
		int i=dayofweek(inputdate.day, inputdate.month, inputdate.year);

		if (i==0)
		{
			calendar[6].day = inputdate.day;
			calendar[6].month = inputdate.month;
			calendar[6].year = inputdate.year;
		}
		else
		{
			calendar[i-1].day = inputdate.day;
			calendar[i-1].month = inputdate.month;
			calendar[i-1].year = inputdate.year;
		}
	}
	else
	{
		errormessage(inputdate);
		goto f;
	}
}


void increment() // This Function generate the next day, month or year: The algorithm of increment is works based on the previous day so after cheching some conditions it increase the date
{
	if (calendar[0].month == 1 || calendar[0].month == 3 || calendar[0].month == 5 || calendar[0].month == 7 || calendar[0].month == 8 || calendar[0].month == 10 || calendar[0].month == 12)// for the month which are 31 days
	{
		for (int i = 0; i <=7 ; i+=1)
		{
			if (calendar[i].day != 0 && calendar[i].month != 0 && calendar[i].year != 0)
			{
				for (int j = 0; j < i; j+=1)
				{
					if (calendar[i].day == 1)
					{
						calendar[j].month = calendar[i].month - 1;
						switch (calendar[j].month)
						{
							/*case 1:
							case 3:
							case 5:*/
							case 7:
							/*case 8:
							case 10:
							case 12:*/
								for (int k = 1; k <dayofweek(calendar[i].day, calendar[i].month, calendar[i].year); k++)
								{
									calendar[j].day = 32 - k;
								}
								break;
						case 2:
							break;						
						case 4:
						case 6:
						case 9:
						case 11:
						
						break;
						}
						
						
						//calendar[j].day == 31;
						
						//calendar[j].day = 1;//trouble
					}
					else
					{
						calendar[j].day = calendar[i].day -1;
						calendar[j].month = calendar[i].month;
					}
					calendar[j].year = calendar[i].year;
				}
			}
		}
		

	}
	else if (calendar[0].month == 4 || calendar[0].month == 6 || calendar[0].month == 9 || calendar[0].month == 11)//for the month which are 30 days
	{
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
	else if (calendar[0].month == 12)// for the last month of the year
	{
		for (int i = 1; i <= 6; i += 1)
		{
			if (calendar[i - 1].day == 31)// if it is last day of the last month the new year will start
			{
				calendar[i].day = 1;
				calendar[i].month = 1;
				calendar[i].year = calendar[i - 1].year + 1;
			}
			else
			{
				calendar[i].day = calendar[i - 1].day + 1;
			}
			calendar[i].month = calendar[0].month;
			calendar[i].year = calendar[0].year;
		}

	}
	else if ((calendar[0].year % 400 == 0 || calendar[0].year % 100 != 0) && calendar[0].year % 4 == 0 && calendar[0].month == 2)//for the second month which can 29 days depends on year(leapyear)
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
	else if (calendar[0].month == 2)//for the second month which can 28 days
	{
		for (int i = 1; i <= 6; i += 1)
		{
			if (calendar[i - 1].day == 28)
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

int dayofweek(int d, int m, int y)// This Function generate the weekdays based on the date
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

string recognizeday()
{
	//string weekday[7];

	for (int i = 0; i < 7; i++)
	{
		switch (dayofweek(calendar[i].day, calendar[i].month, calendar[i].year))
		{
		case 1:
			return "Mon";
			break;
		case 2:
			return "Tue";
			break;
		case 3:
			return "Wed";
			break;
		case 4:
			return "Thu";
			break;
		case 5:
			return "Fri";
			break;
		case 6:
			return "Sat";
			break;
		case 0:
			return "Sun";
			break;
		}
	}
}

void output()// This Function output the results to user
{
	string event[7];
	cout << "Date? " << calendar[0].day << " " << calendar[0].month << " " << calendar[0].year << endl;
	increment();

	string weekday[7];

	for (int i = 0; i < 7; i++)
	{
		switch (dayofweek(calendar[i].day, calendar[i].month, calendar[i].year))
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
		case 0:
			weekday[i] = "Sun";
			break;
		}

		if (calendar[i].day <= 31 && calendar[i].day >= 28)//The last day of the month
		{
			if ((calendar[i].month == 1 || calendar[i].month == 3 || calendar[i].month == 5 || calendar[i].month == 7 || calendar[i].month == 8 || calendar[i].month == 10 || calendar[i].month == 12) && calendar[i].day == 31 && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)//if the month is 31 days and it is also friday
			{
				event[i] = MyHappenings[0].event + " , " + MyHappenings[2].event;
			}
			else if ((calendar[i].month == 1 || calendar[i].month == 3 || calendar[i].month == 5 || calendar[i].month == 7 || calendar[i].month == 8 || calendar[i].month == 10 || calendar[i].month == 12) && calendar[i].day == 31) //if the month is 31 days
			{
				event[i] = MyHappenings[0].event;
			}
			else if ((calendar[i].month == 4 || calendar[i].month == 6 || calendar[i].month == 9 || calendar[i].month == 11) && calendar[i].day == 30 && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)//if the month is 30 days and it is also friday
			{
				event[i] = MyHappenings[0].event + " , " + MyHappenings[2].event;
			}
			else if ((calendar[i].month == 4 || calendar[i].month == 6 || calendar[i].month == 9 || calendar[i].month == 11) && calendar[i].day == 30)//if the month is 30 days
			{
				event[i] = MyHappenings[0].event;
			}
			else if (calendar[i].month == 2 && calendar[i].day == 29 && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5) //if the second month is 29 days and it is also friday
			{
				event[i] = MyHappenings[0].event + " , " + MyHappenings[2].event;
			}
			else if (calendar[i].month == 2 && calendar[i].day == 29)//if the second month is 29 days
			{
				event[i] = MyHappenings[0].event;
			}
			else if (calendar[i].month == 2 && ((calendar[i].year % 400 == 0 || calendar[0].year % 100 != 0) && calendar[i].year % 4 != 0) && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)//if the second month is 28 days and it is also friday
			{
				event[i] = MyHappenings[0].event;
			}
			else if (calendar[i].month == 2 && ((calendar[i].year % 400 == 0 || calendar[0].year % 100 != 0) && calendar[i].year % 4 != 0))//if the second month is 28 days
			{
				event[i] = MyHappenings[0].event;
			}
			else // if there is no event on that date
			{
				event[i] = "-";
			}
		}
		else if (calendar[i].day == 1 && calendar[i].month == 3 && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)//Birthday at 1.3 which might be friday
		{
			event[i] = MyHappenings[1].event + " , " + MyHappenings[3].event;
		}
		else if (calendar[i].day == 1 && calendar[i].month == 3)//Birthday at 1.3
		{
			event[i] = MyHappenings[1].event;
		}
		else if (calendar[i].day == 13 && dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)//"Friday the 13th"
		{
			event[i] = MyHappenings[3].event + " , " + MyHappenings[2].event;
		}
		else if (dayofweek(calendar[i].day, calendar[i].month, calendar[i].year) == 5)// Darts on Fridays
		{
			event[i] = MyHappenings[2].event;
		}
		else
		{
			event[i] = "-";
		}
	}

	for (int i = 0; i <= 6; i += 1)// print the result
	{
		cout << calendar[i].day << "." << calendar[i].month << "." << calendar[i].year << " " << "[" << weekday[i] << "]" << " " << event[i] << endl;
	}
}



int main()
{
	Date dateparam;
	input(dateparam);
	output();
	string buffer;
	cin >> buffer;
	return 0;
}