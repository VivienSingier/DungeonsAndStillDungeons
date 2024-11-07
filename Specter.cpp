#include "Specter.h"
#include "Player.h"
#include "Room.h"
#include "GameManager.h"

Specter::Specter(int x, int y, int difficulty, int index) : Monster::Monster(x, y, " S ", 2, 15, index, 5, "SPECTER")
{
	mAttack += 1 * difficulty;
	mMaxHealth += 5 * difficulty;
	mHealth += 5 * difficulty;
	mActionMessage = "The Specter attacked you";
	mDeathMessage = "You killed the Specter";
}

void Specter::Reward(Player* player)
{
	player->mHealth = player->mMaxHealth;
}

void Specter::Move()
{
	GameManager* gameManager = GameManager::GetInstance();
	int newX = mCoordX;
	int newY = mCoordY;
	int playerX = gameManager->mPlayer->mCoordX;
	int playerY = gameManager->mPlayer->mCoordY;

	if (playerX > newX)
	{
		if (newX > 0)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX - 1, newY))
			{
				newX--;
			}
		}
	}
	if (playerX < newX)
	{
		if (newX < 10)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX + 1, newY))
			{
				newX++;
			}
		}
	}
	if (playerY > newY)
	{
		if (newY > 0)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX, newY - 1))
			{
				newY--;
			}
		}
	}
	if (playerY < newY)
	{
		if (newY < 10)
		{
			if (gameManager->mCurrentRoom->CheckIsEmpty(newX, newY + 1))
			{
				newY++;
			}
		}
	}

	gameManager->mCurrentRoom->MoveEntity(this, newX, newY);
}
