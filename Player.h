#pragma once
#include "Entity.h"
#include "Monster.h"
#include "Room.h"
#include "Door.h"

class Player : public Entity
{
	int mHealth;
	int mMaxHealth;
	int mAttack;
	int mDefense;

public:
	Player(int x, int y);
	void TakeDamage(int damage);
	void DealDamage(Monster* monster);
	int FindClosestEnnemie(Monster** monsterArray);
	void MoveX(int direction, Room* room);
	void MoveY(int direction, Room* room);
	void GoThroughDoor(Door* door);
};

