#pragma once
#include "Date.h"

class TimeStamp : public Date
{
public:
	TimeStamp(int iHour, int iMinute, int iDay, int iMonth, int iYear, bool &pbSuccess);
	~TimeStamp();

	double operator-(TimeStamp &pcOther);

	TimeStamp operator+(double dHours);
	TimeStamp operator-(double dHours);

	std::string sGetDate();

private:
	TimeStamp(double dSecsPassedSinceEpoch);

	bool b_check_and_fix_hour_and_minute(int &piHour, int &piMinute);
	bool b_check_and_fix_hour(int &piHour);
	bool b_check_and_fix_minute(int &piMinute);

	double d_passed_current_day_secs(int iHour, int iMinute);

	void v_get_daytime(int &piHour, int &piMinute);

};//class TimeStamp