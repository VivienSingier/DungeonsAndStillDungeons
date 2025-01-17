#pragma once

class Entity;
class Player;
class Monster;
class Door;

class Room
{
	int mDifficulty;

	int mNumReaper;
	int mNumGolem;
	int mNumSpecter;

public:
	static int mCounter;

	Entity*** mRoomArray;
	Room* mNeighbours[4];
	int mMonsterCounter;
	Monster** mMonsterArray;
	Door** mDoorArray;


	Room();
	Room(Room* neighbour, int direction, int difficulty);
	void MoveEntity(Entity* pEntity, int x, int y);
	void RemoveEntity(Entity* pEntity);
	void AddPlayer(Player* player, int x, int y);
	void AddIntoMonsterArray(Monster* pMonster);
	void RemoveMonster(Monster* pMonster);
	bool CheckIsEmpty(int x, int y);
	bool CheckIsDoor(int x, int y);
	bool CheckIsRoomEmpty();
	void PlaceDoors();
	void PlaceEnnemies();
	void Display();
};

