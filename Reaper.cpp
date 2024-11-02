#include "Reaper.h"

Reaper::Reaper(int x, int  y, int difficulty) : Monster::Monster(x, y, " R ", 5, 25)
{
	mAttack += 2 * difficulty;
	mMaxHealth += 4 * difficulty;
	mHealth += 4 * difficulty;

	mHealValue = 12 + 4 * difficulty;
}
