#include "Room.h"
#include "Door.h"
#include "Golem.h"
#include "Specter.h"
#include "Reaper.h"
#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "RoomGen.h"

#include "GameManager.h"
#include "Entity.h"
#include "Monster.h"
#include "Player.h"

int Room::mCounter = 0;

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
	Room::mCounter++;

	mRoomArray = new Entity**[11];
	for (int i = 0; i < 11; i++)
	{
		mRoomArray[i] = new Entity*[11];
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mRoomArray[i][j] = nullptr;
		}
	}

	mDoorArray = new Door * [4];
	for (int i = 0; i < 4; i++)
	{
		mDoorArray[i] = nullptr;
	}

	mMonsterCounter = 0;
	mMonsterArray = new Monster * [0];

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
	Room::mCounter++;

	mRoomArray = new Entity ** [11];
	for (int i = 0; i < 11; i++)
	{
		mRoomArray[i] = new Entity*[11];
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mRoomArray[i][j] = nullptr;
		}
	}

	mDoorArray = new Door * [4];
	for (int i = 0; i < 4; i++)
	{
		mDoorArray[i] = nullptr;
	}

	mMonsterCounter = 0;
	mMonsterArray = new Monster * [0];

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
			if (Room::mCounter < 11)
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
	if (x != pEntity->mCoordX || y != pEntity->mCoordY)
	{
		mRoomArray[y][x] = pEntity;

		mRoomArray[pEntity->mCoordY][pEntity->mCoordX] = nullptr;
		pEntity->mCoordX = x;
		pEntity->mCoordY = y;
	}
}

void Room::RemoveEntity(Entity* pEntity)
{
	int x = pEntity->mCoordX;
	int y = pEntity->mCoordY;
	mRoomArray[y][x] = nullptr;
}

void Room::AddPlayer(Player* player, int x, int y)
{
	if (mRoomArray[y][x] != nullptr)
	{
		RemoveEntity(mRoomArray[y][x]);
	}
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
	GameManager::GetInstance()->mTotalMonsterCount--;
}

bool Room::CheckIsEmpty(int x, int y)
{
	return mRoomArray[y][x] == nullptr;
}

bool Room::CheckIsDoor(int x, int y)
{
	if (mRoomArray[y][x] == nullptr)
	{
		return false;
	}
	return mRoomArray[y][x]->mDisplay == " D ";
}

bool Room::CheckIsRoomEmpty()
{
	if (mMonsterCounter == 0)
	{
		return true;
	}
	return false;
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
		mDoorArray[3] = newDoor;
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

		Monster* newMonster = new Golem(j, i, mDifficulty, mMonsterCounter);
		mRoomArray[i][j] = newMonster;
		AddIntoMonsterArray(newMonster);
		GameManager::GetInstance()->mTotalMonsterCount++;
	}

	for (int k = 0; k < mNumSpecter; k++)
	{
		int index = rand() % availableCoordCount;
		int i = availableCoordArray[index][0];
		int j = availableCoordArray[index][1];
		RemoveFromArray(&availableCoordArray, index, &availableCoordCount);

		Monster* newMonster = new Specter(j, i, mDifficulty, mMonsterCounter);
		mRoomArray[i][j] = newMonster;
		AddIntoMonsterArray(newMonster);
		GameManager::GetInstance()->mTotalMonsterCount++;
	}

	for (int k = 0; k < mNumReaper; k++)
	{
		int index = rand() % availableCoordCount;
		int i = availableCoordArray[index][0];
		int j = availableCoordArray[index][1];
		RemoveFromArray(&availableCoordArray, index, &availableCoordCount);

		Monster* newMonster = new Reaper(j, i, mDifficulty, mMonsterCounter);
		mRoomArray[i][j] = newMonster;
		AddIntoMonsterArray(newMonster);
		GameManager::GetInstance()->mTotalMonsterCount++;
	}
	
	// TENTATIVE GENERATION PROCEDURALE CONTROLLE
	//RoomGen::Init();
	//int layout;
	//int numMonster;
	//int numReaper = 0;
	//int typeMonster;
	//Monster* newMonster = nullptr;
	//int** Coords;

	//switch (mDifficulty)
	//{
	//default:
	//	layout = RoomGen::Room8Spots;
	//	Coords = RoomGen::Room8AvailableCoords;
	//	numMonster = rand() % 8 + 5;
	//	break;
	//case 0:
	//case 1:
	//	numMonster = rand() % 4 + 1;
	//	layout = RoomGen::Room4Spots;
	//	Coords = RoomGen::Room4AvailableCoords;
	//	break;
	//case 2:
	//case 3:
	//	numMonster = rand() % 5 + 2;
	//	layout = RoomGen::Room5Spots;
	//	Coords = RoomGen::Room5AvailableCoords;
	//	break;
	//case 4:
	//case 5:
	//	numMonster = rand() % 6 + 3;
	//	layout = RoomGen::Room6Spots;
	//	Coords = RoomGen::Room6AvailableCoords;
	//	break;
	//case 6:
	//case 7:
	//	numMonster = rand() % 7 + 4;
	//	layout = RoomGen::Room7Spots;
	//	Coords = RoomGen::Room7AvailableCoords;
	//	break;
	//}

	//numMonster = layout + 4;


	//for (int i = 0; i < 4 + layout; i++)
	//{
	//	int x = Coords[i][0];
	//	int y = Coords[i][1];
	//	int typeMonster = rand() % 3;
	//	switch (typeMonster)
	//	{
	//	case 0:
	//		newMonster = new Golem(x, y, mDifficulty, mMonsterCounter);
	//		break;
	//	case 1:
	//		newMonster = new Specter(x, y, mDifficulty, mMonsterCounter);
	//		break;
	//	case 2:
	//		newMonster = new Reaper(x, y, mDifficulty, mMonsterCounter);
	//		numReaper++;
	//		break;
	//	}
	//	mRoomArray[y][x] = newMonster;
	//	AddIntoMonsterArray(newMonster);
	//	GameManager::GetInstance()->mTotalMonsterCount++;
	//}
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
			if (mRoomArray[i][j] != nullptr)
			{
				Utils::SetColor(mRoomArray[i][j]->mColor, BLACK);
				std::cout << mRoomArray[i][j]->mDisplay;
				Utils::ResetColor();
			}
			else
			{
				std::cout << "   ";
			}
		}
		std::cout << "|" << std::endl;
	}
	DisplayLine();
}

