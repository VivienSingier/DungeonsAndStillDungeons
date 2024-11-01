#pragma once
#include "Room.h"
#include "Entity.h"

class Door : public Entity
{
	int mDirection;

public:
	Door(int x, int y, int direction);	
};

