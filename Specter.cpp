#include "Specter.h"

Specter::Specter(int x, int y, int difficulty, int index) : Monster::Monster(x, y, " S ", 2, 15, index, 5, "SPECTER")
{
	mAttack += 1 * difficulty;
	mMaxHealth += 5 * difficulty;
	mHealth += 5 * difficulty;

	mFleeDistance = 1 + difficulty;
}
