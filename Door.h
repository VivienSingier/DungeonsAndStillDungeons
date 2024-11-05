#pragma once
#include "Entity.h"

class Room;

class Door : public Entity
{
public:
	int mDirection;
	Room* mRoom;

public:
	Door(int x, int y, int direction, Room* room);	
};

