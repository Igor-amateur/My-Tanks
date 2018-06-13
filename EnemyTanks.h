#pragma once
#include "Tanks.h"
class EnemyTanks :
	public Tanks
{
public:
	EnemyTanks(Direction dr, Status st, POINT currentPoint, Battlefield * bf);
	~EnemyTanks()override;
	void Move(int&) override;
	bool LastLife() override;

private:
	void SetStep(int y, int x);
	enum { Up =  0, Down = 1, Left = 2, Right = 3 };
	bool EnemyTanks::SearchEnemy();
	char DirectionToSymbol(const int) const override;
	bool ChoiceDirection();
//	static POINT m_FatePoint;	// Transfer information about the enemy
	bool m_fire;
};

