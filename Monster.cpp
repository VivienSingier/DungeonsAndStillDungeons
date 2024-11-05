#include "Monster.h"
#include <iostream>

int Monster::mCounter = 0;

Monster::Monster(int x, int y, const char* display, int attack, int maxHealth, int index, int color, const char* name) : Character(x, y, display, attack, maxHealth, color)
{
	Monster::mCounter++;
	mRoomIndex = index;
	mName = name;
}

void Monster::DisplayStats()
{
	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
	std::cout << "   " << mName << std::endl;
	Character::DisplayStats();
	std::cout << std::endl;
	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}
