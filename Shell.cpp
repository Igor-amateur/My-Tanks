#include "stdafx.h"
#include "Shell.h"
#include "Battlefield.h"
#include "Flash.h"


const char SHELL_MAX(-7);
const char SHELL_MIN(-6);

Shell::Shell(const Tanks * shooter)
	: Tanks(shooter->GetDirection(), (Status::Invader == shooter->GetStatus()
		? Status::Shell_Invader : Status::Shill_Liberator), shooter->GetPoint(), shooter->GetBattlefield())
	, m_direction(shooter->GetDirection())
{
	SetSymbol(SHELL_MAX);
	m_parentStatus = shooter->GetStatus();
	switch (m_direction)
	{
	case Direction::Up:
		SetFirstStep(-1, 0);
		break;
	case Direction::Left:
		SetFirstStep(0, -1);
		break;
	case Direction::Right:
		SetFirstStep(0, 1);
		break;
	case Direction::Down:
		SetFirstStep(1, 0);
		break;
	default:
		delete this;
		break;
	}

}


Shell::~Shell()
{
}

void Shell::Move(int & dr)
{
	//Beep(600, 50);
	
	if (!m_stopMove)
	{
		SetSymbol(SHELL_MIN);
		switch (m_direction)
		{
		case Direction::Left:
			SetNextStep(0, -1);
			break;
		case Direction::Up:
			SetNextStep(-1, 0);
			break;
		case Direction::Down:
			SetNextStep(1, 0);
			break;
		case Direction::Right:
			SetNextStep(0, 1);
			break;
		default:
			break;
		}
	}
	else
	{
		m_stopMove = false;
	}
	
}

bool Shell::LastLife()
{
	return false;
}

Shell::Direction Shell::GetDirection() const
{
	return m_direction;
}

void Shell::SetStopMove(bool stop)
{
	m_stopMove = stop;
}

void Shell::SetNextStep(int y, int x)
{
	int nextPos_Y = m_currentPoint.y + y;
	int nextPos_X = m_currentPoint.x + x;

	if (mp_battlefield->GetLocation(nextPos_Y, nextPos_X) == nullptr)
	{
		mp_battlefield->SetLocation(nextPos_Y, nextPos_X, this);
		mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, nullptr);
		m_currentPoint.y = nextPos_Y;
		m_currentPoint.x = nextPos_X;
	}
	else if (mp_battlefield->GetLocation(nextPos_Y, nextPos_X)->GetStatus() ==
		Status::Neutral ||
		mp_battlefield->GetLocation(nextPos_Y, nextPos_X)->GetStatus() ==
		m_parentStatus)
	{
		mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, nullptr);
		delete this;
	}
	else if (mp_battlefield->GetLocation(nextPos_Y, nextPos_X)->GetStatus() ==
		Status::Shell_Invader ||
		mp_battlefield->GetLocation(nextPos_Y, nextPos_X)->GetStatus() ==
		Status::Shill_Liberator)
	{//If the path of the projectile
		Shell * aShillPtr = dynamic_cast<Shell*>(mp_battlefield->GetLocation(nextPos_Y, nextPos_X));
		if (aShillPtr == nullptr)
		{
			return;
		}
		if (y > 0 || y < 0 && 
			(Direction)aShillPtr->GetDirection() == Direction::Up ||
			(Direction)aShillPtr->GetDirection() == Direction::Down)
		{
			mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, aShillPtr);
			aShillPtr->SetPoint(m_currentPoint.y, m_currentPoint.x);
			if (y < 0)
			{
				aShillPtr->SetStopMove(true);
			}
			mp_battlefield->SetLocation(nextPos_Y, nextPos_X, this);
			this->SetPoint(nextPos_Y, nextPos_X);
			if (y > 0)
			{
				this->SetStopMove(true);
			}
		}
		else if (x > 0 || x < 0 &&
			(Direction)aShillPtr->GetDirection() == Direction::Left ||
			(Direction)aShillPtr->GetDirection() == Direction::Right)
		{
			mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, aShillPtr);
			aShillPtr->SetPoint(m_currentPoint.y, m_currentPoint.x);
			if (x < 0)
			{
				aShillPtr->SetStopMove(true);
			}
			mp_battlefield->SetLocation(nextPos_Y, nextPos_X, this);
			this->SetPoint(nextPos_Y, nextPos_X);
			if (x > 0)
			{
				this->SetStopMove(true);
			}
		}
		aShillPtr = nullptr;
	}
	else
	{
		if (mp_battlefield->GetLocation(nextPos_Y, nextPos_X)->LastLife())
		{
			delete mp_battlefield->GetLocation(nextPos_Y, nextPos_X);//change for trensformation
			POINT point;
			point.x = nextPos_X;
			point.y = nextPos_Y;
			mp_battlefield->SetLocation(nextPos_Y, nextPos_X, new Flash(GetDirection(), 
				GetStatus(), point, GetBattlefield()));//change for trensformation
		}
		mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, nullptr);
		delete this;
	}
}

void Shell::SetFirstStep(int y, int x)
{
	int firstPos_Y = m_currentPoint.y + y;
	int firstPos_X = m_currentPoint.x + x;

	if (mp_battlefield->GetLocation(firstPos_Y, firstPos_X) == nullptr)
	{
		mp_battlefield->SetLocation(firstPos_Y, firstPos_X, this);
		m_currentPoint.y = firstPos_Y;
		m_currentPoint.x = firstPos_X;
		if (x > 0 || y > 0)
		{
			m_stopMove = true; //Avoiding auto-transitions
		}
		else
		{
			m_stopMove = false;
		}
	}
	else
	{
		if (mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->GetStatus() ==
			Status::Neutral ||
			mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->GetStatus() ==
			this->GetStatus() ||
			mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->GetStatus() == 
			m_parentStatus)
		{
			delete this;
		}
		else
		{
			if (this->GetStatus() == Status::Shill_Liberator)
			{
				if (mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->GetStatus() !=
					Status::Shell_Invader)//if not an enemy shell
				{
					if (mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->LastLife())
					{
						POINT point;
						point.y = firstPos_Y;
						point.x = firstPos_X;
						delete mp_battlefield->GetLocation(firstPos_Y, firstPos_X);//change for trensformation
						mp_battlefield->SetLocation(firstPos_Y, firstPos_X, new Flash(GetDirection(),
							GetStatus(), point, GetBattlefield()));//change for trensformation
					}
					if (mp_battlefield->GetLocation(m_currentPoint.y, m_currentPoint.x)->LastLife())
					{
						delete mp_battlefield->GetLocation(m_currentPoint.y, m_currentPoint.x);//change for trensformation
						mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, new Flash(GetDirection(),
							GetStatus(), m_currentPoint, GetBattlefield()));//change for trensformation
					}
				}
			}
			else
			{
				if (mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->GetStatus() !=
					Status::Shill_Liberator)//if not an enemy shell
				{
					if (mp_battlefield->GetLocation(firstPos_Y, firstPos_X)->LastLife()
						&&
						mp_battlefield->GetLocation(m_currentPoint.y, firstPos_X)->LastLife())
					{
						POINT point;
						point.y = firstPos_Y;
						point.x = firstPos_X;
						delete mp_battlefield->GetLocation(firstPos_Y, firstPos_X);//change for trensformation
						mp_battlefield->SetLocation(firstPos_Y, firstPos_X, new Flash(GetDirection(),
							GetStatus(), point, GetBattlefield()));//change for trensformation

						delete mp_battlefield->GetLocation(m_currentPoint.y, m_currentPoint.x);//change for trensformation
						mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, new Flash(GetDirection(),
							GetStatus(), m_currentPoint, GetBattlefield()));//change for trensformation

					}
				}
			}
			delete this;
		}
	}
}