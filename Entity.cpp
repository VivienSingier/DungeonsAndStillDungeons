#include "Entity.h"
#include <iostream>

Entity::Entity()
{
	mCoordX = 0;
	mCoordY = 0;
	mDisplay = "   ";
	mColor = 15;
}

Entity::Entity(int x, int y, const char* display, int color)
{
	mCoordX = x;
	mCoordY = y;
	mDisplay = display;
	mColor = color;
}

int Entity::GetDistance(Entity* pEntity)
{
	int distanceX = mCoordX - pEntity->mCoordX;
	if (distanceX < 0)
	{
		distanceX *= -1;
	}
	int distanceY = mCoordY - pEntity->mCoordY;
	if (distanceY < 0)
	{
		distanceY *= -1;
	}
	return distanceX + distanceY;
}
