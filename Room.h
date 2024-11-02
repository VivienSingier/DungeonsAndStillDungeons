#pragma once
#include "Entity.h"

class Room
{
	static int mCouter;
	static int mRoomAvailable;

	Entity*** mRoomArray;
	Room* mNeighbours[4];

	bool mIsClear;
	int mDifficulty;

	int mNumReaper;
	int mNumGolem;
	int mNumSpecter;

public:
	Room();
	Room(Room* neighbour, int direction, int difficulty);
	void PlaceDoors();
	void PlaceEnnemies();
	void Display();
};

