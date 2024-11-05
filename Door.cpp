#include "Door.h"
#include "Room.h"

Door::Door(int x, int y, int direction, Room* room) : Entity::Entity(x, y, " D ", 2)
{
	mDirection = direction;
	mRoom = room;
}