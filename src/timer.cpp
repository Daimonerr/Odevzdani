#include "timer.h"

CTimer::CTimer():c_min(0), c_sec(0), c_msec(0)
{}

void CTimer::addTime()
{
	c_msec += 2;

	if (c_msec == 100)
	{
		c_sec++;
		c_msec = 0;
	}

	if (c_sec == 60)
	{
		c_min++;
		c_sec = 0;
	}
}

string CTimer::printTime()
{
	if ( c_sec <= 9 )
		return to_string(c_min) + ":" + "0" + to_string(c_sec);
	return to_string(c_min) + ":" + to_string(c_sec);
}

int CTimer::getMsec()
{
	return c_msec;
}

int CTimer::getPlaytime()
{
	return (c_min*60)+c_sec;
}

int CTimer::endTime(const int & plusT)
{
	return (c_min*60)+c_sec+plusT;
}