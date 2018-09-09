#pragma once
#include "Location.h"


	

	namespace MyTanks
	{
		class Battlefield;

		class Tanks :
			public Location
		{
		public:

			enum class Direction {
				Direct_Error = 0, Left = 75, Right = 77, Down = 80, Up = 72
			};

			enum class Symbol {
				eLeft = -76, eUp = -63, eDown = -62, eRight = -61,
				mLeft = 60, mRight = 62, mDown = 118, mUp = 94
			};

			Tanks(Direction, Status, POINT, Battlefield * bf);
			~Tanks() override;
			void Move(int&) override;
			POINT GetPoint() const;
			virtual Direction GetDirection() const;
			Battlefield * Tanks::GetBattlefield() const;
			void SetPoint(POINT);
			void SetPoint(int, int);
			virtual bool LastLife();

		protected:

			virtual char DirectionToSymbol(const int) const;
			Direction SymbolToDirection(const Symbol) const;
			POINT m_currentPoint;
			Battlefield * mp_battlefield;
			int m_live;

			clock_t m_TimeOld;
			clock_t m_TimeOldFire;


		private:
			virtual void SetStep(int y, int x, int & dr);

		};

	}