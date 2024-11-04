#include "Reaper.h"
#include "Player.h"
#include <cstdlib>

Reaper::Reaper(int x, int  y, int difficulty, int index) : Monster::Monster(x, y, " R ", 5, 25, index)
{
	mAttack += 2 * difficulty;
	mMaxHealth += 4 * difficulty;
	mHealth += 4 * difficulty;

	mHealValue = 12 + 4 * difficulty;
}

void Reaper::TakeDamage(int damage)
{
	Character::TakeDamage(damage);

	int r = rand() % 100;
	if (r < 15 && mIsAlive)
	{
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
