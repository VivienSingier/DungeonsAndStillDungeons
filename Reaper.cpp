#include "Reaper.h"
#include "Player.h"
#include "GameManager.h"
#include "Room.h"
#include <cstdlib>

Reaper::Reaper(int x, int  y, int difficulty, int index) : Monster::Monster(x, y, " R ", 5, 25, index, 4, "REAPER")
{
	mAttack += 2 * difficulty;
	mMaxHealth += 4 * difficulty;
	mHealth += 4 * difficulty;
	mActionMessage = "The Reaper attacked you";
	mDeathMessage = "You killed the Reaper";
	mHealValue = 12 + 4 * difficulty;
}

void Reaper::TakeDamage(int damage)
{
	Character::TakeDamage(damage);

	mActionMessage = "The Reaper attacked you";
	int r = rand() % 100;
	if (r < 15 && mIsAlive)
	{
		mActionMessage = "The Reaper healed himself with his special ability and attacked you";
		if (mHealth <= mMaxHealth - mHealValue)
		{
			mHealth += mHealValue;
		}
		else
		{
			mHealth = mMaxHealth;
		}
	}
}

void Reaper::Reward(Player* player)
{
	player->mMaxHealth += 5;
}

void Reaper::Move()
{
	GameManager* gameManager = GameManager::GetInstance();
	int newX = mCoordX;
	int newY = mCoordY;
	int playerX = gameManager->mPlayer->mCoordX;
	int playerY = gameManager->mPlayer->mCoordY;

	if (playerX > newX)
	{
		if (newX < 10)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX + 1, newY))
			{
				newX++;
			}
		}
	}
	if (playerX < newX)
	{
		if (newX > 0)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX - 1, newY))
			{
				newX--;
			}
		}
	}
	if (playerY > newY)
	{
		if (newY < 10)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX, newY + 1))
			{
				newY++;
			}
		}
	}
	if (playerY < newY)
	{
		if (newY > 0)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX, newY - 1))
			{
				newY--;
			}
		}
	}

	gameManager->mCurrentRoom->MoveEntity(this, newX, newY);
}
