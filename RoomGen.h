#pragma once

namespace RoomGen
{
	enum RoomOptions
	{
		Room4Spots,
		Room5Spots,
		Room6Spots,
		Room7Spots,
		Room8Spots,
		Count
	};

	extern int** Room4AvailableCoords;

	extern int** Room5AvailableCoords;

	extern int** Room6AvailableCoords;

	extern int** Room7AvailableCoords;

	extern int** Room8AvailableCoords;

	void Init();
}