#pragma once
class Entity
{
public:
	int mCoordX;
	int mCoordY;
	const char* mDisplay;

	Entity();
	Entity(int x, int y, const char* display);
};

