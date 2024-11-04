#pragma once
#include "Entity.h"
#include "Monster.h"

class Room
{
	static int mCouter;

	Entity*** mRoomArray;
	Room* mNeighbours[4];

	int mMonsterCounter;
	Monster** mMonsterArray;

	bool mIsClear;
	int mDifficulty;

	int mNumReaper;
	int mNumGolem;
	int mNumSpecter;

public:
	Room();
	Room(Room* neighbour, int direction, int difficulty);
	void SwapEntities(Entity* pEntity1, Entity* pEntity2);
	void RemoveEntity(Entity* pEntity);
	void AddIntoMonsterArray(Monster* pMonster);
	void RemoveMonster(Monster* pMonster);
	void PlaceDoors();
	void PlaceEnnemies();
	void Display();
};

