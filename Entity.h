#pragma once
class Entity
{
protected:
	int mCoordX;
	int mCoordY;
	const char* mDisplay;

public:
	Entity();
	Entity(int x, int y, const char* display);
};

