#include "Player.h"

Player::Player(int x, int  y) : Entity::Entity(x, y, " @ ")
{
	mHealth = 30;
	mMaxHealth = 30;
	mAttack = 5;
	mDefense = 0;
}

void Player::TakeDamage(int damage)
{
	if (mHealth > damage)
	{
		mHealth -= damage;
	}
	else
	{
		mHealth = 0;
	}
}

void Player::DealDamage(Monster* monster)
{
	monster->TakeDamage(mAttack);
}