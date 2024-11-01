#include "Room.h"
#include "Door.h"
#include <cstdlib>

int Room::mCouter = 0;

Room::Room()
{
	Room::mCouter++;

	mRoomArray = new Entity**[11];
	for (int i = 0; i < 11; i++)
	{
		mRoomArray[i] = new Entity*[11];
	}

	mIsClear = false;

	mNumGolem = rand() % 3 + 1;
	mNumReaper = rand() % 2 + 1;
	mNumSpecter = rand() % 3 + 1;

	for (int i = 0; i < 4; i++)
	{
		int isRoom = rand() % 2;
		if (isRoom)
		{
			mNeighbours[i] = new Room(3, this, i);
		}
		else
		{
			mNeighbours[i] = nullptr;
		}
	}
	PlaceDoors();
}

Room::Room(int numRoom, Room* neighbour, int direction)
{
	Room::mCouter++;

	mRoomArray = new Entity ** [11];
	for (int i = 0; i < 11; i++)
	{
		mRoomArray[i] = new Entity*[11];
	}

	mIsClear = false;

	mNumGolem = rand() % 3 + 1;
	mNumReaper = rand() % 2 + 1;
	mNumSpecter = rand() % 3 + 1;

	for (int i = 0; i < 4; i++)
	{
		int isRoom = rand() % 4;
		if (!isRoom)
		{
			if (numRoom > 0)
			{
				mNeighbours[i] = new Room(numRoom - 1, this, i);
			}
		}
		else
		{
			mNeighbours[i] = nullptr;
		}
	}
	PlaceDoors();
}

void Room::PlaceDoors()
{
	if (mNeighbours[0] != nullptr)
	{
		mRoomArray[0][5] = new Door(0, 5, 0);
	}
	if (mNeighbours[1] != nullptr)
	{
		mRoomArray[5][11] = new Door(5, 11, 1);
	}
	if (mNeighbours[2] != nullptr)
	{
		mRoomArray[11][5] = new Door(11, 5, 2);
	}
	if (mNeighbours[3] != nullptr)
	{
		mRoomArray[5][0] = new Door(5, 0, 3);
	}
}


