#pragma once
#include "Location.h"

namespace MyTanks
{
	class Wall :
		public Location
	{
	public:
		Wall()noexcept;
		~Wall()override;

		void Move(int& dr)override {/*do nothing*/ }
		bool LastLife() override { return false; }
	};
}
