#include "Door.h"

Door::Door(int x, int y, int direction) : Entity::Entity(x, y, "   ")
{
	mDirection = direction;
}