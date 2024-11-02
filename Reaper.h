#pragma once
#include "Monster.h"

class Reaper : public Monster
{
	int mHealValue;

public:
	Reaper(int x, int y, int difficulty);
};

