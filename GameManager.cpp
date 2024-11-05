#include "GameManager.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>

GameManager::GameManager()
{
	mCurrentRoom = new Room();
	mPlayer = new Player(5, 5);
	mIsPlaying = true;

	mCurrentRoom->AddPlayer(mPlayer, 5, 5);
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
		}
	}

}

void GameManager::MoveX(int direction)
{
	if (mCurrentRoom->CheckIsEmpty(mPlayer->mCoordX + direction, mPlayer->mCoordY))
	{
		mCurrentRoom->SwapEntities(mPlayer, mCurrentRoom->mRoomArray[mPlayer->mCoordY][mPlayer->mCoordX + direction]);
	}
}

void GameManager::Update()
{
	int input = GetInput();

	switch (input)
	{
	default:
		
		return;
	case 1:
		MoveX(1);
		
		return;
	case 3:
		MoveX(-1);
		
		return;
	}
}

void GameManager::Display()
{
	mCurrentRoom->Display();
}

void GameManager::GameLoop()
{
	while (mIsPlaying)
	{
		Display();
		Update();
	}
}

