#include "Date.h"

Date::Date(int iDay, int iMonth, int iYear, bool &pbSuccess)
{
	pbSuccess = b_check_and_fix_date(iDay, iMonth, iYear);
	d_secs_passed_since_epoch = d_count_passed_secs_since_epoch(iDay, iMonth, iYear);
}//Time::Time(int iDay, int iMonth, int iYear)

Date::Date(double dSecsPassedSinceEpoch)
{
	d_secs_passed_since_epoch = dSecsPassedSinceEpoch;
}//Time::Time(int iDaysPassedSinceEpoch)

Date::~Date()
{
}//Time::~Time()

std::string Date::sGetDate()
{
	std::string s_result;
	int i_current_day;
	int i_current_month;
	int i_current_year;
	v_get_int_date(i_current_day, i_current_month, i_current_year);

	s_result = std::to_string(i_current_day) + "." + std::to_string(i_current_month) + "." + std::to_string(i_current_year);

	return s_result;
}//std::string Time::sGetDate()

int Date::operator-(Date & pcOtherTime)
{
	return i_convert_to_days(d_secs_passed_since_epoch - pcOtherTime.d_secs_passed_since_epoch);
}//int Time::operator-(Time & pcOtherTime)

Date Date::operator+(int iDays)
{
	return Date(d_secs_passed_since_epoch+iDays);
}//Time Time::operator+(int iDays)

Date Date::operator-(int iDays)
{
	return Date(d_secs_passed_since_epoch-iDays);
}//Time Time::operator-(int iDays)

bool Date::operator<(Date & pcOtherTime)
{
	return d_secs_passed_since_epoch < pcOtherTime.d_secs_passed_since_epoch;
}//bool Time::operator<(Time & pcOtherTime)

bool Date::operator<=(Date & pcOtherTime)
{
	return d_secs_passed_since_epoch <= pcOtherTime.d_secs_passed_since_epoch;
}//bool Time::operator<=(Time & pcOtherTime)

bool Date::operator>(Date & pcOtherTime)
{
	return d_secs_passed_since_epoch > pcOtherTime.d_secs_passed_since_epoch;
}//bool Time::operator>(Time & pcOtherTime)

bool Date::operator>=(Date & pcOtherTime)
{
	return d_secs_passed_since_epoch >= pcOtherTime.d_secs_passed_since_epoch;
}//bool Time::operator>=(Time & pcOtherTime)

bool Date::operator==(Date & pcOtherTime)
{
	return d_secs_passed_since_epoch == pcOtherTime.d_secs_passed_since_epoch;
}//bool Time::operator==(Time & pcOtherTime)

void Date::v_get_current_day_and_month(double d_passed_current_year_secs, int i_current_year, int& i_current_month, int& i_current_day)
{
	i_current_month = 1;
	int i_days_counter = i_convert_to_days(d_passed_current_year_secs) + 1;

	bool b_is_correct_date = false;
	while (!b_is_correct_date)
	{
		if (i_current_month == MONTH_FEBRUARY)
		{
			if (b_is_leap_year(i_current_year))
			{
				if (i_days_counter>DAYS_IN_LEAP_YEAR_FEBRUARY)
				{
					i_days_counter -= DAYS_IN_LEAP_YEAR_FEBRUARY;
					i_current_month++;
				}
				else
				{
					b_is_correct_date = true;
				}
			} 
			else if (i_days_counter>DAYS_IN_REGULAR_YEAR_FEBRUARY)
			{
				i_days_counter -= DAYS_IN_REGULAR_YEAR_FEBRUARY;
				i_current_month++;
			}
			else
			{
				b_is_correct_date = true;
			}
		}
		else if (b_is_short_month(i_current_month))
		{
			if (i_days_counter > DAYS_IN_SHORT_MONTH)
			{
				i_days_counter -= DAYS_IN_SHORT_MONTH;
				i_current_month++;
			}
			else
			{
				b_is_correct_date = true;
			}
		}
		else if (b_is_long_month(i_current_month))
		{
			if (i_days_counter>DAYS_IN_LONG_MONTH)
			{
				i_days_counter -= DAYS_IN_LONG_MONTH;
				i_current_month++;
			}
			else
			{
				b_is_correct_date = true;
			}
		}
	}
	i_current_day = i_days_counter;
}//void Time::v_get_current_day_and_month(double d_count_passed_current_year_secs, int i_current_year, int& i_current_month, int& i_current_day)

void Date::v_get_int_date(int& i_current_day, int& i_current_month, int& i_current_year)
{
	int i_years_passed_since_epoch = d_secs_passed_since_epoch / (DAYS_IN_REGULAR_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	int i_leap_years = i_leap_years_between(EPOCH_YEAR, EPOCH_YEAR + i_years_passed_since_epoch);
	i_current_year = EPOCH_YEAR + i_years_passed_since_epoch;

	double d_passed_current_year_secs = d_secs_passed_since_epoch - (i_years_passed_since_epoch - i_leap_years)*(DAYS_IN_REGULAR_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE) - i_leap_years*(DAYS_IN_LEAP_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	if (d_passed_current_year_secs < 0)
	{
		i_current_year--;
		b_is_leap_year(i_current_year) ? d_passed_current_year_secs += (DAYS_IN_LEAP_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE) : d_passed_current_year_secs += (DAYS_IN_REGULAR_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	}

	v_get_current_day_and_month(d_passed_current_year_secs, i_current_year, i_current_month, i_current_day);
}//void Time::v_get_int_date(int& i_current_day, int& i_current_month, int& i_current_year)

int Date::i_leap_years_between(int iStartYear, int iEndYear)
{
	if(iStartYear > iEndYear)
	{
		return -i_leap_years_between(iEndYear, iStartYear);
	}

	int i_leap_years_counter = 0;
	for (int ii = iStartYear; ii < iEndYear; ii++)
	{
		if (b_is_leap_year(ii))
		{
			i_leap_years_counter++;
		}
	}
	return i_leap_years_counter;
}//int Time::i_leap_years_between(int iStartYear, int iEndYear)

double Date::d_count_passed_current_year_secs(int iDay, int iMonth, int iYear)
{
	double d_passed_days = iDay-1;
	int	i_short_months = i_count_passed_short_months(iMonth);
	int	i_long_months = i_count_passed_long_months(iMonth);

	if(iMonth > MONTH_FEBRUARY)
	{
		if(b_is_leap_year(iYear))
		{
			d_passed_days += DAYS_IN_LEAP_YEAR_FEBRUARY;
		}
		else
		{
			d_passed_days += DAYS_IN_REGULAR_YEAR_FEBRUARY;
		}
		d_passed_days += i_short_months*DAYS_IN_SHORT_MONTH;
	}
	d_passed_days += i_long_months*DAYS_IN_LONG_MONTH;

	return d_passed_days * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
}//int Time::d_count_passed_current_year_secs(int iDay, int iMonth, int iYear)

int Date::i_count_passed_short_months(int iMonth)
{
	int i_short_months_counter = 0;
	for(int ii=1; ii<iMonth; ii++)
	{
		if(b_is_short_month(ii))
		{
			i_short_months_counter++;
		}
	}
	return i_short_months_counter;
}//int Time::i_count_passed_short_months(int iMonth)

int Date::i_count_passed_long_months(int iMonth)
{
	int i_long_month_counter = 0;
	for (int ii = 0; ii<iMonth; ii++)
	{
		if (b_is_long_month(ii))
		{
			i_long_month_counter++;
		}
	}
	return i_long_month_counter;
}//int Time::i_count_passed_long_months(int iMonth)

bool Date::b_is_leap_year(int iYear)
{
	return (iYear % 400 == 0 || iYear % 100 != 0) && (iYear % 4 == 0);
}//bool Time::b_is_leap_year(int iYear)

int Date::i_convert_to_days(double dSeconds)
{
	return dSeconds/(HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
}//int Time::i_convert_to_days(double dSeconds)

double Date::d_count_passed_secs_since_epoch(int iDay, int iMonth, int iYear)
{
	double d_passed_seconds = d_count_passed_current_year_secs(iDay, iMonth, iYear);
	int i_leap_years = i_leap_years_between(EPOCH_YEAR, iYear);
	int i_regular_years = iYear - EPOCH_YEAR - i_leap_years;
	d_passed_seconds += i_leap_years * (DAYS_IN_LEAP_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE) + i_regular_years * (DAYS_IN_REGULAR_YEAR * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	
	return d_passed_seconds;
}//int Time::d_count_passed_secs_since_epoch(int iDay, int iMonth, int iYear)


bool Date::b_check_and_fix_date(int & piDay, int & piMonth, int & piYear)
{
	return b_check_and_fix_month(piMonth) && b_check_and_fix_day(piDay, piMonth, piYear);;
}//bool Time::b_check_and_fix_date(int & piDay, int & piMonth, int & piYear)

bool Date::b_check_and_fix_month(int& piMonth)
{
	if (piMonth<1)
	{
		piMonth = 1;
		return false;
	}
	else if (piMonth > MONTHS_IN_YEAR)
	{
		piMonth = MONTHS_IN_YEAR;
		return false;
	}
	return true;
}//void Time::b_check_and_fix_month(int& piMonth, bool& b_result)

bool Date::b_is_short_month(int& piMonth)
{
	return (piMonth % 2 == 0 && piMonth!=MONTH_FEBRUARY && piMonth < MONTH_AUGUST) || (piMonth % 2 == 1 && piMonth >= MONTH_AUGUST);
}//bool Time::b_is_short_month(int& piMonth)

bool Date::b_is_long_month(int& piMonth)
{
	return piMonth % 2 == 1 && piMonth < MONTH_AUGUST || piMonth % 2 == 0 && piMonth >= MONTH_AUGUST;
}//bool Time::b_is_long_month(int& piMonth)

bool Date::b_check_and_fix_day(int& piDay, int& piMonth, int& piYear)
{
	if (piDay < 1)
	{
		piDay = 1;
		return false;
	}
	else if (piMonth == MONTH_FEBRUARY && piDay>DAYS_IN_REGULAR_YEAR_FEBRUARY)
	{
		if (b_is_leap_year(piYear))
		{
			piDay = DAYS_IN_LEAP_YEAR_FEBRUARY;
		}
		else
		{
			piDay = DAYS_IN_REGULAR_YEAR_FEBRUARY;
		}
		return  false;
	}
	else if (b_is_short_month(piMonth)  && piDay>DAYS_IN_SHORT_MONTH)
	{
		piDay = DAYS_IN_SHORT_MONTH;
		return false;
	}
	else if (b_is_long_month(piMonth) && piDay > DAYS_IN_LONG_MONTH)
	{
		piDay = DAYS_IN_LONG_MONTH;
		return false;
	}
	return true;
}//void Time::b_check_and_fix_day(int& piDay, int& piMonth, int& piYear, bool& bResult)