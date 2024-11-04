#pragma once
#include "Character.h"

class Player;

class Monster : public Character
{
	static int mCounter;

public:
	int mRoomIndex;

	Monster(int x, int y, const char* display, int attack, int maxHealth, int index);
	virtual void Reward(Player* player) {}
	virtual void SpecialAbility() {}
	void DisplayStats() override;
};

