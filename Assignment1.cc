/* 
First Assignment
Date is simple triplet of three numbers, Year, Month and Day. Dene
a structure to store this information and dene functions to input, output
and increment a date.
Then create main program, which reads a date from user and outputs
seven consecutive dates after and including date given by user.
For example:
clip>main();
Give date: 1 2 2016
1.2.2016
2.2.2016
3.2.2016
4.2.2016
5.2.2016
6.2.2016
7.2.2016
Value of the expression: 0, type: int
clip>
Remember to handle special cases (change of month, change of year,
leapyears, ...) correctly. Program should be able to handle any date after
1.1.1754 (start of Gregorian calendar in Finland).
 */
struct Date
{
	int day;
	int month;
	int year;
};

Date calendar[7]={{0,0,0}};

void input()
{
	int day;
	int month;
	int year;
	cout<<"Please enter the day"<<endl;
	cin>>day;
	cout<<"Please enter the month"<<endl;
	cin>>month;
	cout<<"Please enter the year"<<endl;
	cin>>year;
	calendar[0].day=day;
	calendar[0].month=month;
	calendar[0].year=year;
}

void output()
{
	cout<<"Given Date: "<<calendar[0].day<<" "<<calendar[0].month<<" "<<calendar[0].year<<endl;
	for(int i=0;i<=6;i+=1)
	{
		cout<<calendar[i].day<<"."<<calendar[i].month<<"."<<calendar[i].year<<endl;
	}
}

void increment()
{

	if(calendar[0].month==1 || calendar[0].month==3 ||calendar[0].month==5 ||calendar[0].month==7 ||calendar[0].month==8 ||calendar[0].month==10 ||calendar[0].month==12  )
	{

			for(int i=0;i<6;i+=1)
			{
				if(calendar[i].day>31)
				{
					calendar[i+1].day-=1;
					calendar[i+1].month+=1;
				}
				else if(calendar[i].day==30)
				{
					calendar[i+1].day+=1;
					calendar[i+1].month=calendar[i].month;
				}
				else if(calendar[i].day==31)
				{
					calendar[i+1].day=1;
					calendar[i+1].month=calendar[i].month+1;
				}
				
								
				calendar[i].year=calendar[0].year;
		}

	}
	else if(calendar[0].month==4 || calendar[0].month==6 ||calendar[0].month==9 ||calendar[0].month==11)
	{
		if(calendar[0].day==28)
		{
			calendar[1].day=calendar[0].day+1;
		}
		else if(calendar[0].day==30)
		{
			calendar[0].day=1;
			calendar[1].month=calendar[0].month+1;
		}
	}
	
	else if(calendar[0].month==12)
	{
		calendar[1].day==1;
		calendar[1].month=1;
		calendar[1].year=calendar[0].year+1;
	}
	else if((calendar[0].year%400==0 || calendar[0].year%100!=0 )&& calendar[0].year%4==0 && calendar[0].month==2 && calendar[0].day==27)
	{
		calendar[1].day=calendar[0].day+1;
	}
	else
	{
		calendar[0].day+=1;
	}
	for(int i=2;i<=6;i+=1)
	{

		calendar[i].month=calendar[0].month;
	
		calendar[i].year=calendar[0].year;

		for(int j=1;j<=6;j+=1)
		{
			calendar[j].day=calendar[0].day+1;
		}
	}
}

int main()
{
	input();
	increment();
	output();
	return 0;
}
