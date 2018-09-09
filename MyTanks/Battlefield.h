#pragma once

#include"Location.h"

namespace MyTanks
{

	int const Width(50);//Battlefield width maximum X value
	int const Height(16);//height of the battlefield maximum value of Y

	class Battlefield
	{
	public:
		Battlefield() noexcept;
		~Battlefield();


		bool Show();//Drawing the battlefield
		Location * GetLocation(int, int);//Get object from (Y X)
		void refresh(int & key);//Update the field configuration
		void Battlefield::SetLocation(int, int, Location *);//Set object to position (Y X)
		int RandFor(int val);//Get a random number from 1 to (val-1)
		void MinusLive();//Decrease Life Count by 1
		void PlusDestroyedTank();//Increase the number of destroyed tanks by 1
	private:
		bool m_gameOver;//initially false
		Location * mp_battlefield[Height][Width]; //array for the battlefield
		int m_Lives;// life counter
		int m_Destroyed;//counter of destroyed enemy tanks
		int m_EnemyTanks;//counter of enemy tanks

	};

}