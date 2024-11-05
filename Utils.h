#pragma once
#include "Windows.h"

#define BLACK 0
#define RED 4
#define GREEN 2
#define YELLOW 6
#define BLUE 1
#define MAGENTA 5
#define CYAN 3
#define WHITE 15
#define LIGHTBLUE 9
#define LIGHTGREEN 10

namespace Utils 
{
	void SetColor(int color, int bgColor);

	void ResetColor();
}
