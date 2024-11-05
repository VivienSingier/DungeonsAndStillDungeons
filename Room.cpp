#include "Room.h"
#include "Door.h"
#include "Golem.h"
#include "Specter.h"
#include "Reaper.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"

#include "Entity.h"
#include "Monster.h"
#include "Player.h"

int Room::mCouter = 0;

int** CreateAvailableCoordArray()
{
	int availableCoordCount = 11 * 11 - 5;
	int** availableCoordArray = new int* [availableCoordCount];

	for (int i = 0; i < availableCoordCount; i++)
	{
		availableCoordArray[i] = new int[2];
	}

	int i = 0;
	int j = 0;
	int k = 0;
	bool isValid = !((i == 0 && j == 5) || (i == 10 && j == 5) || (i == 5 && j == 0) || (i == 5 && j == 10) || (i == 5 && j == 5));

	while (k < availableCoordCount)
	{
		bool isValid = !((i == 0 && j == 5) || (i == 10 && j == 5) || (i == 5 && j == 0) || (i == 5 && j == 10) || (i == 5 && j == 5));
		if (isValid)
		{
			availableCoordArray[k][0] = i;
			availableCoordArray[k][1] = j;
			k++;
		}
		j++;
		if (j == 11)
		{
			i++;
			j = 0;
		}
	}
	return availableCoordArray;
}

void RemoveFromArray(int*** pArray, int index, int* size)
{
	*size = *size - 1;
	int** arr = *pArray;

	for (int i = index; i < *size; i++)
	{
		arr[i][0] = arr[i + 1][0];
		arr[i][1] = arr[i + 1][1];
	}

	int** newArray = new int* [*size];
	for (int i = 0; i < *size; i++)
	{
		newArray[i] = new int[2];
	}

	for (int i = 0; i < *size; i++)
	{
		newArray[i][0] = arr[i][0];
		newArray[i][1] = arr[i][1];
	}

	delete[] * pArray;
	*pArray = newArray;
}

Room::Room()
{
	Room::mCouter++;

	mRoomArray = new Entity**[11];
	for (int i = 0; i < 11; i++)
	{
		mRoomArray[i] = new Entity*[11];
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mRoomArray[i][j] = new Entity(j, i, "   ", 15);
		}
	}

	mDoorArray = new Door * [4];
	for (int i = 0; i < 4; i++)
	{
		mDoorArray[i] = nullptr;
	}

	mMonsterCounter = 0;
	mMonsterArray = new Monster * [0];

	mIsClear = false;
	mDifficulty = 0;

	mNumGolem = rand() % 3 + 1;
	mNumReaper = rand() % 2 + 1;
	mNumSpecter = rand() % 3 + 1;

	for (int i = 0; i < 4; i++)
	{
		int isRoom = rand() % 2;
		if (!isRoom)
		{
			mNeighbours[i] = new Room(this, i, mDifficulty + 1);
		}
		else
		{
			mNeighbours[i] = nullptr;
		}
	}
	PlaceDoors();
	PlaceEnnemies();
}

Room::Room(Room* neighbour, int direction, int difficulty)
{
	Room::mCouter++;

	mRoomArray = new Entity ** [11];
	for (int i = 0; i < 11; i++)
	{
		mRoomArray[i] = new Entity*[11];
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mRoomArray[i][j] = new Entity(j, i, "   ", 15);
		}
	}

	mDoorArray = new Door * [4];
	for (int i = 0; i < 4; i++)
	{
		mDoorArray[i] = nullptr;
	}

	mMonsterCounter = 0;
	mMonsterArray = new Monster * [0];

	mIsClear = false;
	mDifficulty = difficulty;

	mNumGolem = rand() % 3 + 1;
	mNumReaper = rand() % 2 + 1;
	mNumSpecter = rand() % 3 + 1;


	direction = (direction + 2) % 4;
	mNeighbours[direction] = neighbour;


	for (int i = 0; i < 4; i++)
	{
		int isRoom = rand() % 4;
		if (!isRoom && i != direction)
		{
			if (Room::mCouter < 11)
			{
				mNeighbours[i] = new Room(this, i, mDifficulty + 1);
			}
		}
		else if (i != direction)
		{
			mNeighbours[i] = nullptr;
		}
	}
	PlaceDoors();
	PlaceEnnemies();
}

void Room::MoveEntity(Entity* pEntity , int x, int y)
{
	delete mRoomArray[y][x];
	mRoomArray[y][x] = pEntity;
	
	mRoomArray[pEntity->mCoordY][pEntity->mCoordX] = new Entity(pEntity->mCoordX, pEntity->mCoordY, "   ", 15);
	pEntity->mCoordX = x;
	pEntity->mCoordY = y;
}

void Room::RemoveEntity(Entity* pEntity)
{
	int x = pEntity->mCoordX;
	int y = pEntity->mCoordY;
	mRoomArray[y][x] = new Entity(x, y, "   ", 15);
}

void Room::AddPlayer(Player* player, int x, int y)
{
	delete mRoomArray[y][x];
	mRoomArray[y][x] = player;
}

void Room::AddIntoMonsterArray(Monster* pMonster)
{
	mMonsterArray = (Monster**)realloc(mMonsterArray, sizeof(Monster*) * (mMonsterCounter + 1));

	mMonsterArray[mMonsterCounter] = pMonster;
	mMonsterCounter += 1;
}

void Room::RemoveMonster(Monster* pMonster)
{
	int index = pMonster->mRoomIndex;
	mMonsterArray[mMonsterCounter - 1]->mRoomIndex = index;
	mMonsterArray[index] = mMonsterArray[mMonsterCounter - 1];

	RemoveEntity(pMonster);
	
	mMonsterArray = (Monster**) realloc(mMonsterArray, sizeof(Monster*) * (mMonsterCounter - 1));

	mMonsterCounter--;
}

bool Room::CheckIsEmpty(int x, int y)
{
	return mRoomArray[y][x]->mDisplay == "   ";
}

void Room::PlaceDoors()
{
	if (mNeighbours[0] != nullptr)
	{
		Door* newDoor = new Door(0, 5, 0, mNeighbours[0]);
		mRoomArray[0][5] = newDoor;
		mDoorArray[0] = newDoor;
	}
	if (mNeighbours[1] != nullptr)
	{
		Door* newDoor = new Door(5, 10, 1, mNeighbours[1]);
		mRoomArray[5][10] = newDoor;
		mDoorArray[1] = newDoor;
	}
	if (mNeighbours[2] != nullptr)
	{	
		Door* newDoor = new Door(10, 5, 2, mNeighbours[2]);
		mRoomArray[10][5] = newDoor;
		mDoorArray[2] = newDoor;
	}
	if (mNeighbours[3] != nullptr)
	{
		Door* newDoor = new Door(5, 0, 3, mNeighbours[3]);
		mRoomArray[5][0] = newDoor;
		mDoorArray[3];
	}
}

void Room::PlaceEnnemies()
{
	int availableCoordCount = 11 * 11 - 5;
	int** availableCoordArray = CreateAvailableCoordArray();

	for (int k = 0; k < mNumGolem; k++)
	{
		int index = rand() % availableCoordCount;
		int i = availableCoordArray[index][0];
		int j = availableCoordArray[index][1];
		RemoveFromArray(&availableCoordArray, index, &availableCoordCount);

		delete mRoomArray[i][j];
		Monster* newMonster = new Golem(j, i, mDifficulty, mMonsterCounter);
		mRoomArray[i][j] = newMonster;
		AddIntoMonsterArray(newMonster);
	}

	for (int k = 0; k < mNumSpecter; k++)
	{
		int index = rand() % availableCoordCount;
		int i = availableCoordArray[index][0];
		int j = availableCoordArray[index][1];
		RemoveFromArray(&availableCoordArray, index, &availableCoordCount);

		delete mRoomArray[i][j];
		Monster* newMonster = new Specter(j, i, mDifficulty, mMonsterCounter);
		mRoomArray[i][j] = newMonster;
		AddIntoMonsterArray(newMonster);
	}

	for (int k = 0; k < mNumReaper; k++)
	{
		int index = rand() % availableCoordCount;
		int i = availableCoordArray[index][0];
		int j = availableCoordArray[index][1];
		RemoveFromArray(&availableCoordArray, index, &availableCoordCount);

		delete mRoomArray[i][j];
		Monster* newMonster = new Reaper(j, i, mDifficulty, mMonsterCounter);
		mRoomArray[i][j] = newMonster;
		AddIntoMonsterArray(newMonster);
	}
}

void DisplayLine()
{
	for (int i = 0; i < 11; i++)
	{
		std::cout << "+---";
	}
	std::cout << "+" << std::endl;
}

void Room::Display()
{
	for (int i = 0; i < 11; i++)
	{
		DisplayLine();
		for (int j = 0; j < 11; j++)
		{
			std::cout << "|";
			Utils::SetColor(mRoomArray[i][j]->mColor, BLACK);
			std::cout << mRoomArray[i][j]->mDisplay;
			Utils::ResetColor();
		}
		std::cout << "|" << std::endl;
	}
	DisplayLine();
}

