#include "stdafx.h"
#include "Wall.h"

namespace MyTanks
{

	const char WALLS(-80);

	Wall::Wall()noexcept :Location(WALLS, Status::Neutral)
	{
	}


	Wall::~Wall()
	{
	}

}