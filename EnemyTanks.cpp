#include "stdafx.h"
#include "EnemyTanks.h"
#include "Battlefield.h"
#include "Shell.h"



EnemyTanks::EnemyTanks(Direction dr, Status st, POINT currentPoint, Battlefield * bf)
	:Tanks(dr, st, currentPoint, bf)
{	
	m_fire = false;
	m_live = 0;

	int direction = bf->RandFor(6)-1; // Generate a random number from 0 to 3

	switch (direction)
	{
	case Up:
		this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Up)));
		break;
	case Down:
		this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Down)));
		break;
	case Left:
		this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Left)));
		break;
	case Right:
		this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Right)));
		break;
	default:
		break;
	}

}


EnemyTanks::~EnemyTanks()
{
	mp_battlefield->PlusDestroyedTank();
}

void EnemyTanks::Move(int& dr)
{
	/////////////GETTING STARTED
	clock_t Time = clock();
	clock_t timeResult = Time - m_TimeOld;
	

	

	m_fire = SearchEnemy();

	if (timeResult >= (5 * TIME_PAUSE))
	{
		m_TimeOld = Time;
		switch (SymbolToDirection((Tanks::Symbol)this->GetSymbol()))
		{
		case Direction::Left:
			SetStep(0, -1);
			break;
		case Direction::Up:
			SetStep(-1, 0);
			break;
		case Direction::Down:
			SetStep(1, 0);
			break;
		case Direction::Right:
			SetStep(0, 1);
			break;
		default:
			break;
		}

		if (m_fire)
		{//If so then shoot
			m_fire = SearchEnemy();
			new Shell(this);
		}
	}
	/////////////END OF MOVEMENT
}

char EnemyTanks::DirectionToSymbol(const int direct) const
{
	switch ((Direction)direct)
	{
	case Direction::Up:
		return static_cast<char>(Symbol::eUp);
	case Direction::Left:
		return static_cast<char>(Symbol::eLeft);
	case Direction::Right:
		return static_cast<char>(Symbol::eRight);
	case Direction::Down:
		return static_cast<char>(Symbol::eDown);
	default:
		return 0;
		break;
	}

}

bool EnemyTanks::ChoiceDirection()
{

	int direction = this->GetBattlefield()->RandFor(6) - 1;//generate random numbers 0 - 3

	switch (direction)
	{
	case Up:
		if (mp_battlefield->GetLocation(m_currentPoint.y - 1, m_currentPoint.x) == nullptr)
		{
			this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Up)));
			return true;
		}
		break;
	case Down:
		if (mp_battlefield->GetLocation(m_currentPoint.y + 1, m_currentPoint.x) == nullptr)
		{
			this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Down)));
			return true;
		}
		break;
	case Left:
		if (mp_battlefield->GetLocation(m_currentPoint.y, m_currentPoint.x - 1) == nullptr)
		{
			this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Left)));
			return true;
		}
		break;
	case Right:
		if (mp_battlefield->GetLocation(m_currentPoint.y, m_currentPoint.x + 1) == nullptr)
		{
			this->SetSymbol(this->DirectionToSymbol(static_cast<int>(Direction::Right)));
			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

bool EnemyTanks::SearchEnemy()
{
	///////////////////////////////////////////////////////////////////////////////////
	int h_ht = this->GetPoint().y;
	int w_th = this->GetPoint().x + 1;
	for (; mp_battlefield->GetLocation(h_ht, w_th) == nullptr ||
		mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Status::Shill_Liberator ; w_th++)
	{
		//Looking for an object in the direction of X (Right)
	}
	
	if (mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Location::Status::Liberator)
	{
	//	m_FatePoint.x = w_th; m_FatePoint.y = h_ht; // inform everyone about the enemy
		this->SetSymbol(this->DirectionToSymbol((int)Tanks::Direction::Right));// Define the direction of shooting
		return true;
	}
	/////
	w_th = this->GetPoint().x - 1;
	for (; mp_battlefield->GetLocation(h_ht, w_th) == nullptr ||
		mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Status::Shill_Liberator	; w_th--)
	{
		//Looking for an object against the direction of X (Left)
	}

	if (mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Location::Status::Liberator)
	{
	//	m_FatePoint.x = w_th; m_FatePoint.y = h_ht; // inform everyone about the enemy
		this->SetSymbol(this->DirectionToSymbol((int)Tanks::Direction::Left));// Define the direction of shooting
		return true;
	}
	///////////////////////////////////////////////////////////////////////////////////
	h_ht = this->GetPoint().y + 1;
	w_th = this->GetPoint().x;
	for (; mp_battlefield->GetLocation(h_ht, w_th) == nullptr ||
		mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Status::Shill_Liberator ; h_ht++)
	{
		//Looking for an object in the direction of the Y (Down)
	}

	if (mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Location::Status::Liberator)
	{
	//	m_FatePoint.x = w_th; m_FatePoint.y = h_ht; // We inform everyone about the enemy
		this->SetSymbol(this->DirectionToSymbol((int)Tanks::Direction::Down));//Define the direction of shooting
		return true;
	}
	/////
	h_ht = this->GetPoint().y - 1;
	for (; mp_battlefield->GetLocation(h_ht, w_th) == nullptr ||
		mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Status::Shill_Liberator ; h_ht--)
	{
		//Looking for an object against the direction of Y (Up)
	}

	if (mp_battlefield->GetLocation(h_ht, w_th)->GetStatus() == Location::Status::Liberator)
	{
	//	m_FatePoint.x = w_th; m_FatePoint.y = h_ht; // inform everyone about the enemy
		this->SetSymbol(this->DirectionToSymbol((int)Tanks::Direction::Up));// Define the direction of shooting
		return true;
	}
	///////////////////////////////////////////////////////////////////////////////////
	return false;
}

void EnemyTanks::SetStep(int y, int x)
{
	int newPos_Y = m_currentPoint.y + y;
	int newPos_X = m_currentPoint.x + x;

	if (mp_battlefield->GetLocation(newPos_Y, newPos_X) == nullptr)
	{//if it's free, go
		mp_battlefield->SetLocation(newPos_Y, newPos_X, this);
		mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, nullptr);
		m_currentPoint.y = newPos_Y;
		m_currentPoint.x = newPos_X;
	}
	else if (mp_battlefield->GetLocation(newPos_Y, newPos_X)->GetStatus() ==
		Status::Shell_Invader ||
		mp_battlefield->GetLocation(newPos_Y, newPos_X)->GetStatus() ==
		Status::Shill_Liberator)
	{//if the shell is in front
	 //We are waiting for nothing.
	}
	else
	{
		int i = 0; //retry count
				   //choose a new direction (maximum 20 attempts)
		while (!ChoiceDirection() && i < 20) { i++; }
	}
}

bool EnemyTanks::LastLife()
{
	return m_live > 0 ? false : true;
}