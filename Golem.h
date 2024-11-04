#pragma once
#include "Monster.h"

class Golem : public Monster
{
	int mResistChance;
	bool mIsResisting;

public:
	Golem(int x, int y, int difficulty, int index);
	void TakeDamage(int damage) override;
	void Reward(Player* player) override;
};

