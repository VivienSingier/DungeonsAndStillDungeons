#include "Utils.h"

namespace Utils
{
	void SetColor(int color, int bgColor)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (bgColor << 4) | color);
	}

	void ResetColor()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (0 << 4) | 7);
	}
}