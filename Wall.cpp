#include "stdafx.h"
#include "Wall.h"


const char WALLS(-80);
Wall::Wall():Location(WALLS, Status::Neutral)
{
}


Wall::~Wall()
{
}
