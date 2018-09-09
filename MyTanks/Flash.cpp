#include "stdafx.h"
#include "Flash.h"
#include"Battlefield.h"

namespace MyTanks
{

	const char FLASH(-2);

	Flash::Flash(Direction dr, Status st, POINT currentPoint, Battlefield * bf)
		:Tanks(dr, st, currentPoint, bf)
		, m_stopDestroy(false)
	{
		if (dr == Direction::Down || dr == Direction::Right)
		{
			m_stopDestroy = true;

		}
		this->SetSymbol(FLASH);
	}


	Flash::~Flash()
	{
	}

	void Flash::Move(int & dr)
	{
		if (!m_stopDestroy)
		{
			mp_battlefield->SetLocation(m_currentPoint.y, m_currentPoint.x, nullptr);
			delete this;
		}
		else
		{
			m_stopDestroy = false;
		}
	}

}