#include "Monster.h"
#include <iostream>

int Monster::mCounter = 0;

Monster::Monster(int x, int y, const char* display, int attack, int maxHealth, int index) : Character(x, y, display, attack, maxHealth)
{
	Monster::mCounter++;
	mRoomIndex = index;
}

void Monster::DisplayStats()
{
	Character::DisplayStats();
	std::cout << std::endl;
	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}
