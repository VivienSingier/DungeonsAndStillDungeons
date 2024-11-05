#pragma once

class Room;
class Player;
class Monster;
class Door;

class GameManager
{
	Room* mCurrentRoom;
	Player* mPlayer;
	Monster* mClosestEnnemie;
	bool mIsPlaying;
	bool mCanAttack;

public:
	GameManager();

	int GetInput();
	bool IsValidCoordinates(int x, int y);
	Monster* GetClosestEnnemie();
	void GoThroughDoor(Door* door);
	void MoveX(int direction);
	void MoveY(int direction);
	void Update();
	void HandleInput();
	void DisplayActions();
	void Display();
	void GameLoop();

};

