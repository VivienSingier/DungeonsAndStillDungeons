#pragma once
#include "Entity.h"
#include "Player.h"

class Monster : public Entity
{
protected:
	int mAttack;
	int mMaxHealth;
	int mHealth;
	// Player player;

public:
	Monster(int x, int y, const char* display, int attack, int maxHealth);
	void TakeDamage(int damage);
	void DealDamage(Player* player);
};

