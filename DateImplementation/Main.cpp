// DateImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Time.h"
#include <iostream>
#include "TimeStamp.h"


int main()
{
	while(true)
	{
		bool  b_suc;
		TimeStamp t3(10, 1, 11, 1, 2017, b_suc);
		TimeStamp t4(12, 1, 11, 1, 2017, b_suc);

		std::cout << t4 - t3 << std::endl;

		int i_hour;
		int i_minute;
		int i_day ;
		int i_month ;
		int i_year ;
		std::cout << "Hour: ";
		std::cin >> i_hour;
		std::cout << "Minute: ";
		std::cin >> i_minute;
		std::cout << "Day: ";
		std::cin >> i_day;
		std::cout << "Month: ";
		std::cin >> i_month; 
		std::cout << "Year: ";
		std::cin >> i_year;
		bool bSucc;
		TimeStamp t(i_hour, i_minute,i_day, i_month, i_year, bSucc);
		TimeStamp t2(12, 12, 1, 1, 2000, bSucc);
		std::cout << t.sGetDate() << std::endl;
	}
	
	return 0;
}//int main()

