#pragma once
#include "Monster.h"

class Reaper : public Monster
{
	int mHealValue;

public:
	Reaper(int x, int y, int difficulty, int index);
	void TakeDamage(int damage) override;
	void Reward(Player* player) override;
	void Move() override;
};

