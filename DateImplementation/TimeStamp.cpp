#include "TimeStamp.h"

TimeStamp::TimeStamp(int iHour, int iMinute, int iDay, int iMonth, int iYear, bool &pbSuccess) : Date(iDay, iMonth, iYear, pbSuccess) 
{
	pbSuccess = b_check_and_fix_hour_and_minute(iHour, iMinute);
	d_secs_passed_since_epoch += d_passed_current_day_secs(iHour, iMinute);
}//TimeStamp::TimeStamp(int iHour, int iMinute, int iDay, int iMonth, int iYear, bool &pbSuccess) : Time(iDay, iMonth, iYear, pbSuccess) 

TimeStamp::TimeStamp(double dSecsPassedSinceEpoch) : Date(dSecsPassedSinceEpoch)
{
}//TimeStamp::TimeStamp(double dSecsPassedSinceEpoch) : Time(dSecsPassedSinceEpoch)


TimeStamp::~TimeStamp()
{
}//TimeStamp::~TimeStamp()

std::string TimeStamp::sGetDate()
{
	std::string s_result;
	int iHour;
	int iMinute;
	v_get_daytime(iHour, iMinute);

	s_result = std::to_string(iHour) + ":" + std::to_string(iMinute) + "\n" + Date::sGetDate();
	return s_result;
}//std::string TimeStamp::sGetDate()

double TimeStamp::operator-(TimeStamp & pcOther)
{
	return (d_secs_passed_since_epoch - pcOther.d_secs_passed_since_epoch)/SECONDS_IN_MINUTE;
}//double TimeStamp::operator-(TimeStamp & pcOther)

TimeStamp TimeStamp::operator+(double dHours)
{
	return TimeStamp(d_secs_passed_since_epoch + dHours*(MINUTES_IN_HOUR * SECONDS_IN_MINUTE));
}//TimeStamp TimeStamp::operator+(double dHours)

TimeStamp TimeStamp::operator-(double dHours)
{
	return TimeStamp(d_secs_passed_since_epoch - dHours*(MINUTES_IN_HOUR * SECONDS_IN_MINUTE));
}//TimeStamp TimeStamp::operator-(double dHours)

bool TimeStamp::b_check_and_fix_hour_and_minute(int & piHour, int & piMinute)
{
	return b_check_and_fix_hour(piHour) && b_check_and_fix_minute(piMinute);
}//bool TimeStamp::b_check_and_fix_hour_and_minute(int & piHour, int & piMinute)

bool TimeStamp::b_check_and_fix_hour(int & piHour)
{
	if(piHour<0)
	{
		piHour = 0;
		return false;
	}
	else if(piHour>(HOURS_IN_DAY-1))
	{
		piHour = HOURS_IN_DAY - 1;
		return false;
	}
	return true;
}//bool TimeStamp::b_check_and_fix_hour(int & piHour)

bool TimeStamp::b_check_and_fix_minute(int & piMinute)
{
	if(piMinute<0)
	{
		piMinute = 0;
		return false;
	}
	else if (piMinute>(MINUTES_IN_HOUR-1))
	{
		piMinute = (MINUTES_IN_HOUR - 1);
		return false;
	}
	return false;
}//bool TimeStamp::b_check_and_fix_minute(int & piMinute)

double TimeStamp::d_passed_current_day_secs(int iHour, int iMinute)
{
	return  iHour*(MINUTES_IN_HOUR * SECONDS_IN_MINUTE) + iMinute*SECONDS_IN_MINUTE;
}//double TimeStamp::d_passed_current_day_secs(int iHour, int iMinute)

void TimeStamp::v_get_daytime(int & piHour, int & piMinute)
{
	double d_passed_current_day_secs = fmod(d_secs_passed_since_epoch, HOURS_IN_DAY * MINUTES_IN_HOUR* SECONDS_IN_MINUTE);
	if(d_passed_current_day_secs < 0)
	{
		d_passed_current_day_secs += HOURS_IN_DAY * MINUTES_IN_HOUR* SECONDS_IN_MINUTE;
	}

	piHour = d_passed_current_day_secs / (MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	piMinute = (d_passed_current_day_secs - piHour * (MINUTES_IN_HOUR * SECONDS_IN_MINUTE)) / SECONDS_IN_MINUTE;
}//void TimeStamp::v_get_daytime(int & piHour, int & piMinute)