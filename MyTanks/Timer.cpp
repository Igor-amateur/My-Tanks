#include "stdafx.h"
#include "Timer.h"
#include <iostream>

namespace MyTimer
{

	Timer::Timer() noexcept : DayPerSec(86400)
		, HourPerSec(3600)
		, MinPerSec(60)
	{
		//clock_t t1 = clock();
		m_t1 = clock();
		m_hour = 0;
		m_minute = 0;
		m_second = 0;
		x_old = 0;
		CalcTime(0);
	}


	Timer::~Timer()
	{
	}

	void Timer::ShowTime()
	{


		int x(0); //time in seconds

		clock_t t2 = clock();
		x = (t2 - m_t1) / CLOCKS_PER_SEC;
		if ((x - x_old))
		{

			CalcTime(x);

			x_old = x;
		}
		std::cout << " TIME " << m_hour << ":" << m_minute << ":" << m_second;
	}
	//Allows you to create an interrupt in milliseconds
	bool Timer::SetInterrupt(int inter)
	{
		Sleep(inter);
		return true;
	}

	void Timer::CalcTime(const int x)
	{
		m_hour = x / HourPerSec; // get the clock
		int rest = x % HourPerSec; // throw the clock, get the minutes in seconds
		m_minute = rest / MinPerSec; // get the minutes
		m_second = rest % MinPerSec;	//throw minutes away
	}

}