#pragma once
class Entity
{
public:
	int mCoordX;
	int mCoordY;
	const char* mDisplay;
	int mColor;

	Entity();
	Entity(int x, int y, const char* display, int color);
	int GetDistance(Entity* pEntity);
};

