#pragma once
#include "Entity.h"

class Room
{
	static int mCouter;

	Entity*** mRoomArray;
	Room* mNeighbours[4];

	bool mIsClear;

	int mNumReaper;
	int mNumGolem;
	int mNumSpecter;

public:
	Room();
	Room(int numRoom, Room* neighbour, int direction);
	void PlaceDoors();
	void PlaceEnnemies();
};

