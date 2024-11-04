#include "Golem.h"
#include "Player.h"
#include <cstdlib>

Golem::Golem(int x, int y, int difficulty, int index) : Monster(x, y, " G ", 3, 35, index)
{
	mAttack += 1 * difficulty;
	mMaxHealth += 7 * difficulty;
	mHealth += 7 * difficulty;

	mResistChance = 30 + 3 * difficulty;
	mIsResisting = false;
}

void Golem::TakeDamage(int damage)
{
	int r = rand() % 100;
	if (r < mResistChance)
	{
		damage = false;
	}
	Character::TakeDamage(damage);
}

void Golem::Reward(Player* player)
{
	player->mAttack += 1;
}
