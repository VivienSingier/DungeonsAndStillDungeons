#pragma once
#include "Character.h"

class Player;

class Monster : public Character
{

public:
	const char* mActionMessage;
	const char* mDeathMessage;
	const char* mName;
	int mRoomIndex;

	Monster(int x, int y, const char* display, int attack, int maxHealth, int index, int color, const char* name);
	virtual void Reward(Player* player) {}
	virtual void SpecialAbility() {}
	virtual void Move() {};
	void DisplayStats() override;
};

