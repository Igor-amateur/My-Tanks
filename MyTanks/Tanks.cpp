#include "stdafx.h"
#include "Tanks.h"
#include"Battlefield.h"
#include "Shell.h"

namespace MyTanks
{
	

	const int FIRE(32);//


	Tanks::Tanks(Direction dr, Status st, POINT currentPoint, Battlefield * bf)
		: Location(DirectionToSymbol((int)dr), st)

	{
		m_live = 5;
		m_TimeOld = 0;
		m_currentPoint = currentPoint;
		mp_battlefield = bf;
		m_TimeOldFire = clock();////////
	}


	Tanks::~Tanks()
	{

		m_live = 0;
	}

	POINT Tanks::GetPoint() const
	{
		return m_currentPoint;
	}

	void Tanks::SetPoint(POINT p)
	{
		m_currentPoint = p;
	}

	void Tanks::SetPoint(int hei, int wid)
	{
		m_currentPoint.x = wid;
		m_currentPoint.y = hei;
	}

	void Tanks::Move(int & dr)
	{
		/////////////GETTING STARTED
		if (this->GetSymbol() == DirectionToSymbol(dr))
		{
			clock_t time = clock();
			clock_t timeResult = time - m_TimeOld;

			if (timeResult >= (5 * TIME_PAUSE))
			{
				m_TimeOld = time;
				switch ((Direction)dr)
				{
				case Direction::Left:
					SetStep(0, -1, dr);
					break;
				case Direction::Up:
					SetStep(-1, 0, dr);
					break;
				case Direction::Down:
					SetStep(1, 0, dr);
					break;
				case Direction::Right:
					SetStep(0, 1, dr);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			switch ((Direction)dr)
			{//Check the symbol to change the direction
			case Direction::Left:
			case Direction::Up:
			case Direction::Down:
			case Direction::Right:
				this->SetSymbol(DirectionToSymbol(dr));
				break;
			default:
				clock_t TimeFire = clock();
				clock_t timeFireResult = TimeFire - m_TimeOldFire;
				if (timeFireResult >= (10 * TIME_PAUSE))//we stand a pause in the shooting
				{
					//Here we check for the press of shooting
					if (FIRE == dr)
					{//If so then we shoot
						new Shell(this);
						m_TimeOldFire = TimeFire;
					}
				}
				break;
			}
			dr = 0;
		}
		///////////// END OF MOVEMENT
	}

	Tanks::Direction Tanks::GetDirection() const
	{
		return SymbolToDirection(static_cast<Symbol>(GetSymbol()));
	}

	Battlefield * Tanks::GetBattlefield() const
	{
		return mp_battlefield;
	}


	char Tanks::DirectionToSymbol(const int direct) const
	{
		switch ((Direction)direct)
		{
		case Direction::Up:
			return (char)Symbol::mUp;
		case Direction::Left:
			return (char)Symbol::mLeft;
		case Direction::Right:
			return (char)Symbol::mRight;
		case Direction::Down:
			return (char)Symbol::mDown;
		default:
			return 0;
			break;
		}

	}

	Tanks::Direction Tanks::SymbolToDirection(const Symbol symbol) const
	{
		switch (symbol)
		{
		case Symbol::eUp:
		case Symbol::mUp:
			return Direction::Up;
		case Symbol::eDown:
		case Symbol::mDown:
			return Direction::Down;
		case Symbol::eLeft:
		case Symbol::mLeft:
			return Direction::Left;
		case Symbol::eRight:
		case Symbol::mRight:
			return Direction::Right;
		default:
			return Direction::Direct_Error;
			break;
		}
	}

	bool Tanks::LastLife()
	{
		mp_battlefield->MinusLive();
		--m_live;
		return m_live > 0 ? false : true;
	}

	void Tanks::SetStep(int y, int x, int & dr)
	{
		int newPos_Y = m_currentPoint.y + y;
		int newPos_X = m_currentPoint.x + x;
		if (mp_battlefield->GetLocation(newPos_Y, newPos_X) == nullptr)
		{
			mp_battlefield->SetLocation(newPos_Y, newPos_X, this);
			mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, nullptr);
			m_currentPoint.y = newPos_Y;
			m_currentPoint.x = newPos_X;
			dr = 0;
		}
	}

}