#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Golem.h"
#include "Room.h"
#include "GameManager.h"

int main()
{
    srand(time(NULL));
    GameManager* gameManager = new GameManager();
    gameManager->GameLoop();
    
    //Player* player = new Player(0, 0);
    //Golem* golem = new Golem(0, 0, 0, 0);

    //for (int i = 0; i < 10; i++)
    //{
    //    player->DealDamage(golem);
    //    golem->DisplayStats();
    //    golem->DealDamage(player);
    //    player->DisplayStats();
    //}
}
