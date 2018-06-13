#pragma once
#include "Tanks.h"

class Flash :
	public Tanks
{
public:
	Flash(Direction dr, Status st, POINT currentPoint, Battlefield * bf);
	~Flash();
	void Move(int&) override;
private:
	bool m_stopDestroy;
};

