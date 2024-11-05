#include "GameManager.h"

#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include "Door.h"

GameManager::GameManager()
{
	mCurrentRoom = new Room();
	mPlayer = new Player(5, 5);
	mClosestEnnemie = GetClosestEnnemie();
	mIsPlaying = true;

	mCurrentRoom->AddPlayer(mPlayer, 5, 5);
}

bool GameManager::IsValidCoordinates(int x, int y)
{
	if (x < 11 && x >= 0)
	{
		if (y < 11 && y >= 0)
		{
			return true;
		}
	}
	return false;
}

int GameManager::GetInput()
{
	char input[2] = { ' ', ' ' };
	
	input[0] = _getch();

	if ((int)input[0] == -32)
	{
		input[1] = _getch();
		switch ((int)input[1])
		{
		case 72:
			//UP
			return 0;
		case 77:
			//RIGHT
			return 1;
		case 80:
			//DOWN
			return 2;
		case 75:
			//LEFT
			return 3;
		}
	}
	else
	{
		switch ((int)input[0])
		{
		case 90:
		case 122:
			// Z -> UP
			return 0;
		case 68:
		case 100:
			// D -> RIGHT
			return 1;
		case 83:
		case 115:
			// S -> DOWN
			return 2;
		case 81:
		case 113:
			// Q -> LEFT
			return 3;
		case 65:
		case 97:
			// A -> ATTACK
			return 4;
		case 69:
		case 101:
			// E - > USE
			return 5;
		}
	}

}

Monster* GameManager::GetClosestEnnemie()
{
	int distance = mPlayer->GetDistance(mCurrentRoom->mMonsterArray[0]);
	Monster* closestEnnemie = mCurrentRoom->mMonsterArray[0];
	for (int i = 1; i < mCurrentRoom->mMonsterCounter; i++)
	{
		int newDistance = mPlayer->GetDistance(mCurrentRoom->mMonsterArray[i]);
		if (newDistance < distance)
		{
			closestEnnemie = mCurrentRoom->mMonsterArray[i];
			distance = newDistance;
		}
	}
	return closestEnnemie;
}

void GameManager::GoThroughDoor(Door* door)
{
	int  CoordArray[4][2] = {
		{10, 5}, {5, 0}, {0, 5}, {5, 10}
	};

	mCurrentRoom->RemoveEntity(mPlayer);
	mCurrentRoom = door->mRoom;
	mCurrentRoom->AddPlayer(mPlayer, CoordArray[door->mDirection][0], CoordArray[door->mDirection][1]);
}

void GameManager::MoveX(int direction)
{
	if (IsValidCoordinates(mPlayer->mCoordX + direction, mPlayer->mCoordY))
	{
		if (mCurrentRoom->CheckIsEmpty(mPlayer->mCoordX + direction, mPlayer->mCoordY))
		{
			mCurrentRoom->MoveEntity(mPlayer, mPlayer->mCoordX + direction, mPlayer->mCoordY);
		}
	}
}

void GameManager::MoveY(int direction)
{
	if (IsValidCoordinates(mPlayer->mCoordX, mPlayer->mCoordY + direction))
	{
		if (mCurrentRoom->CheckIsEmpty(mPlayer->mCoordX, mPlayer->mCoordY + direction))
		{
			mCurrentRoom->MoveEntity(mPlayer, mPlayer->mCoordX, mPlayer->mCoordY + direction);
		}
	}
}

void GameManager::HandleInput() 
{
	int input = GetInput();

	switch (input)
	{
	default:
		return;
	case 0:
		MoveY(-1);
		return;
	case 1:
		MoveX(1);
		return;
	case 2:
		MoveY(1);
		return;
	case 3:
		MoveX(-1);
		return;
	case 4:
		if (mCanAttack)
		{
			mPlayer->DealDamage(mClosestEnnemie);
			mClosestEnnemie->DealDamage(mPlayer);
			mClosestEnnemie->SpecialAbility();
		}
		if (!mClosestEnnemie->mIsAlive)
		{
			mClosestEnnemie->Reward(mPlayer);
			mCurrentRoom->RemoveMonster(mClosestEnnemie);
		}
	}
}

void GameManager::Update()
{
	mCanAttack = false;
	if (mCurrentRoom->mMonsterCounter > 0)
	{
		mClosestEnnemie = GetClosestEnnemie();
	}
	if (mPlayer->GetDistance(mClosestEnnemie) == 1)
	{
		mCanAttack = true;
	}
	if (!mPlayer->mIsAlive)
	{
		mIsPlaying = false;
	}
}

void GameManager::DisplayActions()
{
	std::cout << "   [ZQSD] MOVE";
	if (mCanAttack)
	{
		std::cout << "   [A] ATTACK";
	}
	std::cout << std::endl;
	std::cout << "+";
	for (int i = 0; i < 43; i++)
	{
		std::cout << "-";
	}
	std::cout << "+" << std::endl;
}

void GameManager::Display()
{
	system("cls");
	mClosestEnnemie->DisplayStats();
	mCurrentRoom->Display();
	mPlayer->DisplayStats();
	DisplayActions();
	std::cout << "Player :" << mPlayer->mCoordX << "|" << mPlayer->mCoordY << std::endl;
	std::cout << "Closest Ennemie :" << mClosestEnnemie->mCoordX << "|" << mClosestEnnemie->mCoordY << "|" << mPlayer->GetDistance(mClosestEnnemie) << std::endl;
} 

void GameManager::GameLoop()
{
	Display();
	while (mIsPlaying)
	{
		Display();
		HandleInput();
		Update();
	}
}

