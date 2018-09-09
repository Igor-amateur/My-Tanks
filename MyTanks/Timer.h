#pragma once

#include <ctime>

namespace MyTimer
{

	class Timer
	{
	public:
		Timer() noexcept;
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
		int x_old;
	private:
		void CalcTime(const int x);

	};

}

