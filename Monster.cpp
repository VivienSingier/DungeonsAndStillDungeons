#include "Monster.h"

Monster::Monster(int x, int y, const char* display, int attack, int maxHealth)
{
	mCoordX = x;
	mCoordY = y;
	mDisplay = display;

	mAttack = attack;
	mMaxHealth = maxHealth;
	mHealth = maxHealth;
}
