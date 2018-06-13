#pragma once

#include <ctime>

class Timer
{
public:
	Timer();
	~Timer();
	void ShowTime();
	bool SetInterrupt(int inter);
private:
	const int DayPerSec;
	const int HourPerSec;
	const int MinPerSec;

	clock_t m_t1;
	int m_hour;
	int m_minute;
	int m_second;
private:
	void CalcTime(const int x);

};

