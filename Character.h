#pragma once
#include "Entity.h"

class Character : public Entity
{
public:
	int mMaxHealth;
	int mHealth;
	int mAttack;
	bool mIsAlive;

	Character(int x, int y, const char* display, int maxHealth, int attack);
	virtual void TakeDamage(int damage);
	void DealDamage(Character* character);
	virtual void DisplayStats();
};

