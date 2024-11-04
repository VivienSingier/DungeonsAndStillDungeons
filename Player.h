#pragma once
#include "Character.h"

class Player : public Character
{
public:
	int mDefense;

	Player(int x, int y);
	void TakeDamage(int damage) override;
	void DisplayStats() override;
};

