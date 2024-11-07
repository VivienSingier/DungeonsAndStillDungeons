#include "GameManager.h"

#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include "Door.h"
#include "AsciiArt.h"

enum RoomType 
{
	Room1,
	Room2,

	Count
};

GameManager* GameManager::mInstance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new GameManager();
	}
	return mInstance;
}

GameManager::GameManager()
{
	mTotalMonsterCount = 0;
	mIsPlaying = true;
	mHasWon = false;
	mHasAttacked = false;
	mCanAttack = false;
}

void GameManager::Init()
{
	mCurrentRoom = new Room();
	mPlayer = new Player(5, 5);
	mClosestEnnemie = GetClosestEnnemie();
	mAttackedMonster = nullptr;
	mActionMessage = GetClosestEnnemie()->mActionMessage;
	mIsPlaying = true;
	mHasWon = false;
	mHasAttacked = false;
	mCanAttack = false;

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
		{5, 9}, {1, 5}, {5, 1}, {9, 5}
	};

	mCurrentRoom->RemoveEntity(mPlayer);
	mCurrentRoom = door->mRoom;
	mPlayer->mCoordX = CoordArray[door->mDirection][0];
	mPlayer->mCoordY = CoordArray[door->mDirection][1];
	mCurrentRoom->AddPlayer(mPlayer, CoordArray[door->mDirection][0], CoordArray[door->mDirection][1]);
}

void GameManager::MoveX(int direction)
{
	if (IsValidCoordinates(mPlayer->mCoordX + direction, mPlayer->mCoordY))
	{
		if (mCurrentRoom->CheckIsDoor(mPlayer->mCoordX + direction, mPlayer->mCoordY))
		{
			Door* door = (Door*)mCurrentRoom->mRoomArray[mPlayer->mCoordY][mPlayer->mCoordX + direction];
			GoThroughDoor(door);
		}
		else if (mCurrentRoom->CheckIsEmpty(mPlayer->mCoordX + direction, mPlayer->mCoordY))
		{
			mCurrentRoom->MoveEntity(mPlayer, mPlayer->mCoordX + direction, mPlayer->mCoordY);
		}
	}
}

void GameManager::MoveY(int direction)
{
	if (IsValidCoordinates(mPlayer->mCoordX, mPlayer->mCoordY + direction))
	{
		if (mCurrentRoom->CheckIsDoor(mPlayer->mCoordX, mPlayer->mCoordY + direction))
		{
			Door* door = (Door*)mCurrentRoom->mRoomArray[mPlayer->mCoordY + direction][mPlayer->mCoordX];
			GoThroughDoor(door);
		}
		else if (mCurrentRoom->CheckIsEmpty(mPlayer->mCoordX, mPlayer->mCoordY + direction))
		{
			mCurrentRoom->MoveEntity(mPlayer, mPlayer->mCoordX, mPlayer->mCoordY + direction);
		}
	}
}

void GameManager::HandleInput() 
{
	mHasAttacked = false;
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
			mActionMessage = mClosestEnnemie->mActionMessage;
			mAttackedMonster = mClosestEnnemie;
			mHasAttacked = true;
			if (!mClosestEnnemie->mIsAlive)
			{
				mClosestEnnemie->Reward(mPlayer);
				mCurrentRoom->RemoveMonster(mClosestEnnemie);
				mActionMessage = mClosestEnnemie->mDeathMessage;
			}
			if (!mCurrentRoom->CheckIsRoomEmpty())
			{
				for (int i = 0; i < mCurrentRoom->mMonsterCounter; i++)
				{
					mCurrentRoom->mMonsterArray[i]->Move();
				}
			}
		}
	}
}

void GameManager::Update()
{
	mCurrentRoom->CheckIsRoomEmpty();
	mCanAttack = false;
	if (mTotalMonsterCount == 0)
	{
		mIsPlaying = false;
		mHasWon = true;
	}
	if (mCurrentRoom->mMonsterCounter > 0)
	{
		mClosestEnnemie = GetClosestEnnemie();
		if (mPlayer->GetDistance(mClosestEnnemie) == 1)
		{
			mCanAttack = true;
		}
	}
	if (!mPlayer->mIsAlive)
	{
		mIsPlaying = false;
	}
}

void GameManager::DisplayInput()
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

void GameManager::DisplayLastActions()
{
	if (mHasAttacked && mCurrentRoom->mMonsterCounter > 0)
	{
		std::cout << "   You attacked the " << mAttackedMonster->mName << " for " << mPlayer->mAttack << " damage";
	}
	std::cout << std::endl;
	if (mHasAttacked && mCurrentRoom->mMonsterCounter > 0)
	{
		std::cout << "   " << mActionMessage; 
		if (mClosestEnnemie->mIsAlive)
		{
			std::cout << " for " << mClosestEnnemie->mAttack << " damage";
		}
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
	DisplayLastActions();
	DisplayInput();
	std::cout << mTotalMonsterCount << "|" << mHasWon << "|" << Room::mCounter;
} 

void GameManager::GameLoop()
{
	Init();

	DisplayAsciiArt(title, 115, 32);
	std::cout << std::endl << "               " << "Enter a key to START";
	_getch();

	Display();
	while (mIsPlaying)
	{
		Display();
		HandleInput();
		Update();
	}

	system("cls");
	if (!mHasWon)
	{
		DisplayAsciiArt(gameOverTxt, 73, 8);
		mTotalMonsterCount = 0;
		std::cout << std::endl << "                   " << "Enter a key to play again";
		_getch();
		GameLoop();
	}
	if (mHasWon)
	{
		DisplayAsciiArt(youWonTxt, 57, 8);
		std::cout << std::endl << "                   " << "Enter a key to play again";
		_getch();
		GameLoop();
	}
}

