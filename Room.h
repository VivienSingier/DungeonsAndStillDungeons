#pragma once
#include "Entity.h"
#include "Monster.h"
#include "Player.h"

class Room
{

	static int mCouter;

	Room* mNeighbours[4];

	int mMonsterCounter;
	Monster** mMonsterArray;

	bool mIsClear;
	int mDifficulty;

	int mNumReaper;
	int mNumGolem;
	int mNumSpecter;

public:
	Entity*** mRoomArray;

	Room();
	Room(Room* neighbour, int direction, int difficulty);
	void SwapEntities(Entity* pEntity1, Entity* pEntity2);
	void RemoveEntity(Entity* pEntity);
	void AddPlayer(Player* player, int x, int y);
	void AddIntoMonsterArray(Monster* pMonster);
	void RemoveMonster(Monster* pMonster);
	bool CheckIsEmpty(int x, int y);
	void PlaceDoors();
	void PlaceEnnemies();
	void Display();
};

