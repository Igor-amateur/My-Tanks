#pragma once
#include "Location.h"
class Wall :
	public Location
{
public:
	Wall();
	~Wall()override;

	void Move(int& dr)override {/*do nothing*/}
	bool LastLife() override { return false; }
};

