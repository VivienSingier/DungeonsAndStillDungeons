#pragma once

class Room;
class Player;
class Monster;
class Door;

class GameManager
{
	static GameManager* mInstance;

	Monster* mClosestEnnemie;
	Monster* mAttackedMonster;
	const char* mActionMessage;
	bool mHasWon;
	bool mIsPlaying;
	bool mCanAttack;
	bool mHasAttacked;

public:
	int mTotalMonsterCount;
	Room* mCurrentRoom;
	Player* mPlayer;

	static GameManager* GetInstance();

	GameManager();
	void Init();

	int GetInput();
	bool IsValidCoordinates(int x, int y);
	Monster* GetClosestEnnemie();
	void GoThroughDoor(Door* door);
	void MoveX(int direction);
	void MoveY(int direction);
	void Update();
	void HandleInput();
	void DisplayInput();
	void DisplayLastActions();
	void Display();
	void GameLoop();

};

