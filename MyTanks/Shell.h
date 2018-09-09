#pragma once
#include "Tanks.h"


class Battlefield;

namespace MyTanks
{

	class Shell :
		public Tanks
	{
	public:
		Shell(const Tanks*);
		~Shell();
		void Move(int&) override;
		bool LastLife() override;
		Direction GetDirection() const;
	private:
		void SetNextStep(int y, int x);//determines all subsequent positions
		void SetFirstStep(int y, int x);//determines the first position
		void SetStopMove(bool stop);//allows to block an auto-transition with the parameter true
	private:
		const Direction m_direction;//The direction is set once and does not change
		bool m_stopMove;//Avoiding auto-transitions
		Status m_parentStatus; //Status of an arrow to identify the enemy
	};

}