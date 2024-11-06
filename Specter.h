#pragma once
#include "Monster.h"

class Specter : public Monster
{
	int mFleeDistance;

public:
	Specter(int x, int y, int difficulty, int index);
	void Reward(Player* player) override;
};

