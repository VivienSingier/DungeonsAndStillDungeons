#include "Player.h"
#include "iostream"

Player::Player(int x, int  y) : Character(x, y, " @ ", 5, 30, 1)
{
	mDefense = 0;
}

void Player::TakeDamage(int damage)
{
	damage -= mDefense;
	Character::TakeDamage(damage);
}

void Player::DisplayStats()
{
	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
	Character::DisplayStats();
	std::cout << "[DFS " << mDefense << "] " << std::endl;

	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}
