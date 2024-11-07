#include "RoomGen.h"


int tempRoom4AvailableCoords[4][2] =
{
	{2, 2},
	{2, 8},
	{8, 2},
	{8, 8}
};

int tempRoom5AvailableCoords[5][2] =
{
	{2, 2},
	{2, 8},
	{8, 2},
	{8, 8},
	{5, 5}
};

int tempRoom6AvailableCoords[6][2] =
{
	{2, 3},
	{2, 7},
	{7, 3},
	{7, 7},
	{5, 1},
	{5, 9}
};

int tempRoom7AvailableCoords[7][2] =
{
	{2, 3},
	{2, 7},
	{7, 3},
	{7, 7},
	{5, 1},
	{5, 9},
	{5, 5}
};

int tempRoom8AvailableCoords[8][2] =
{
	{1, 1},
	{1, 9},
	{3, 6},
	{4, 2},
	{6, 8},
	{7, 4},
	{9, 1},
	{9, 9}
};

namespace RoomGen
{
	void Init()
	{
		int** Room4AvailableCoords = new int* [4];
		for (int i = 0; i < 4; i++)
		{
			Room4AvailableCoords[i] = tempRoom4AvailableCoords[i];
		}

		int** Room5AvailableCoords = new int* [5];
		for (int i = 0; i < 5; i++)
		{
			Room5AvailableCoords[i] = tempRoom5AvailableCoords[i];
		}

		int** Room6AvailableCoords = new int* [6];
		for (int i = 0; i < 6; i++)
		{
			Room6AvailableCoords[i] = tempRoom6AvailableCoords[i];
		}

		int** Room7AvailableCoords = new int* [7];
		for (int i = 0; i < 7; i++)
		{
			Room7AvailableCoords[i] = tempRoom7AvailableCoords[i];
		}

		int** Room8AvailableCoords = new int* [8];
		for (int i = 0; i < 7; i++)
		{
			Room8AvailableCoords[i] = tempRoom8AvailableCoords[i];
		}
	}
}