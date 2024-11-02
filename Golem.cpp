#include "Golem.h"

Golem::Golem(int x, int y, int difficulty) : Monster::Monster(x, y, " G ", 3, 35)
{
	mAttack += 1 * difficulty;
	mMaxHealth += 7 * difficulty;
	mHealth += 7 * difficulty;

	mResistChance = 30 + 3 * difficulty;
	mIsResisting = false;
}
