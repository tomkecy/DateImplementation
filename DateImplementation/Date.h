#pragma once
#define EPOCH_YEAR 1970

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_REGULAR_YEAR 31536000
#define SECONDS_IN_LEAP_YEAR 31622400

#define MINUTES_IN_HOUR 50
#define HOURS_IN_DAY 24

#define DAYS_IN_REGULAR_YEAR_FEBRUARY 28
#define DAYS_IN_LEAP_YEAR_FEBRUARY 29
#define DAYS_IN_SHORT_MONTH 30
#define DAYS_IN_LONG_MONTH 31
#define DAYS_IN_REGULAR_YEAR 365
#define DAYS_IN_LEAP_YEAR 366

#define MONTHS_IN_YEAR 12

#define MONTH_FEBRUARY 2
#define MONTH_AUGUST 8

#include <string>

class Date
{
public:
	
	Date(int iDay, int iMonth, int iYear, bool &pbSuccess);
	virtual ~Date();
	
	Date operator+(int iDays);
	Date operator-(int iDays);

	bool operator<(Date& pcOtherTime);
	bool operator<=(Date& pcOtherTime);
	bool operator>(Date& pcOtherTime);
	bool operator>=(Date& pcOtherTime);
	bool operator==(Date& pcOtherTime);

	int operator-(Date& pcOtherTime);

	virtual std::string sGetDate();

protected:
	Date(double dSecsPassedSinceEpoch);

	bool b_check_and_fix_date(int &piDay, int &piMonth, int &piYear);
	bool b_check_and_fix_day(int& piDay, int& piMonth, int& piYear);
	bool b_check_and_fix_month(int& piMonth);

	bool b_is_short_month(int& piMonth);
	bool b_is_long_month(int& piMonth);
	bool b_is_leap_year(int iYear);

	double d_count_passed_secs_since_epoch(int iDay, int iMonth, int iYear);
	double d_count_passed_current_year_secs(int iDay, int iMonth, int iYear);

	void v_get_current_day_and_month(double dPassedCurrentYearSecs, int iCurrentYear, int& iCurrentMonth, int& iCurrentDay);
	void v_get_int_date(int& iCurrentDay, int& iCurrentMonth, int& iCurrentYear);
	
	int i_convert_to_days(double dSeconds);
	int i_leap_years_between(int iStartYear, int iEndYear);
	int i_count_passed_short_months(int iMonth);
	int i_count_passed_long_months(int iMonth);

	double d_secs_passed_since_epoch;
};//class Time