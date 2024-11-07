#include <iostream>
#include <cstdlib>
#include "GameManager.h"
#pragma once

int main()
{
    srand(time(NULL));
    GameManager* gameManager = GameManager::GetInstance();
    gameManager->GameLoop();
}
