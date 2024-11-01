#include "Entity.h"

Entity::Entity()
{
	mCoordX = 0;
	mCoordY = 0;
	mDisplay = "   ";
}

Entity::Entity(int x, int y, const char* display)
{
	mCoordX = x;
	mCoordY = y;
	mDisplay = display;
}
