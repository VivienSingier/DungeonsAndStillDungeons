#pragma once
#include "Room.h"
#include "Player.h"

class GameManager
{
	Room* mCurrentRoom;
	Player* mPlayer;
	bool mIsPlaying;

public:
	GameManager();

	int GetInput();
	void MoveX(int direction);
	void MoveY(int direction);
	void Update();
	void Display();
	void GameLoop();

};

