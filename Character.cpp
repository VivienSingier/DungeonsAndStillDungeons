#include "Character.h"
#include <iostream>
#include <Windows.h>
#include "utils.h"

Character::Character(int x, int y, const char* display, int attack, int maxHealth, int color) : Entity(x, y, display, color)
{
	mAttack = attack;
	mMaxHealth = maxHealth;
	mHealth = maxHealth;
	mIsAlive = true;
}

void Character::TakeDamage(int damage)
{
	if (damage >= mHealth)
	{
		mHealth = 0;
		mIsAlive = false;
	}
	else
	{
		mHealth -= damage;
	}
}

void Character::DealDamage(Character* character)
{
	character->TakeDamage(mAttack);
}

void Character::DisplayStats()
{
	int healthCubes = (int)(((float) mHealth / (float) mMaxHealth) * 10);
	std::cout << "   HP   ";
	Utils::SetColor(BLACK, RED);
	if (mHealth == mMaxHealth)
	{
		for (int i = 0; i < healthCubes; i++)
		{
			std::cout << "[]";
		}
	}
	else
	{
		for (int i = 0; i < healthCubes - 1; i++)
		{
			std::cout << "[]";
		}
		if (mHealth > 0)
		{
			Utils::SetColor(BLACK, YELLOW);
			std::cout << "[]";
		}
	}
	Utils::ResetColor();
	for (int i = 0; i < 10 - healthCubes; i++)
	{
		std::cout << "[]";
	}
	std::cout << " " << mHealth << "/" << mMaxHealth;

	std::cout << std::endl;

	std::cout << "   [ATK " << mAttack << "] ";

}
						