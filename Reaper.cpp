#include "Reaper.h"
#include "Player.h"
#include <cstdlib>

Reaper::Reaper(int x, int  y, int difficulty, int index) : Monster::Monster(x, y, " R ", 5, 25, index, 4, "REAPER")
{
	mAttack += 2 * difficulty;
	mMaxHealth += 4 * difficulty;
	mHealth += 4 * difficulty;
	mActionMessage = "The Reaper attacked you";
	mDeathMessage = "You killed the Reaper";
	mHealValue = 12 + 4 * difficulty;
}

void Reaper::TakeDamage(int damage)
{
	Character::TakeDamage(damage);

	mActionMessage = "The Reaper attacked you";
	int r = rand() % 100;
	if (r < 15 && mIsAlive)
	{
		mActionMessage = "The Reaper healed himself with his special ability and attacked you";
		if (mHealth <= mMaxHealth - mHealValue)
		{
			mHealth += mHealValue;
		}
		else
		{
			mHealth = mMaxHealth;
		}
	}
}
