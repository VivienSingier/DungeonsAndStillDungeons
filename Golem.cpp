#include "Golem.h"
#include "Player.h"
#include <cstdlib>

Golem::Golem(int x, int y, int difficulty, int index) : Monster(x, y, " G ", 2, 30, index, 6, "GOLEM")
{
	mAttack += 1 * difficulty;
	mMaxHealth += 4 * difficulty;
	mHealth += 4 * difficulty;
	mActionMessage = "The Golem attacked you";
	mDeathMessage = "You killed the Golem";
	mResistChance = 30;
	mIsResisting = false;
}

void Golem::TakeDamage(int damage)
{
	mActionMessage = "The Golem attacked you";
	int r = rand() % 100;
	if (r < mResistChance)
	{
		damage = 0;
		mActionMessage = "The Golem protected himself with it's special ability and attacked you";
	}
	Character::TakeDamage(damage);
}

void Golem::Reward(Player* player)
{
	player->mAttack += 1;
}
