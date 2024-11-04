#include "Character.h"
#include <iostream>
#include <Windows.h>

#define BLACK 0
#define RED 4
#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define MAGENTA 5
#define CYAN 3
#define WHITE 15
#define LIGHTBLUE 9
#define LIGHTGREEN 10

void SetColor(int color, int bgColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | color);
}

void ResetColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (0 << 4) | 7);
}

Character::Character(int x, int y, const char* display, int attack, int maxHealth) : Entity(x, y, display)
{
	mAttack = attack;
	mMaxHealth = maxHealth;
	mHealth = maxHealth;
	mIsAlive = true;
}

void Character::TakeDamage(int damage)
{
	if (damage > mHealth)
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
	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;

	int healthCubes = (int)(((float) mHealth / (float) mMaxHealth) * 10);
	std::cout << "HP        ";
	SetColor(BLACK, RED);
	for (int i = 0; i < healthCubes; i++)
	{
		std::cout << "[]";
	}
	ResetColor();
	for (int i = 0; i < 10 - healthCubes; i++)
	{
		std::cout << "[]";
	}
	std::cout << std::endl;

	std::cout << "[ATK " << mAttack << "] ";

}
