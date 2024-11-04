#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Golem.h"
#include "Room.h"

int main()
{
    srand(time(NULL));
    Room* room1 = new Room();
    
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
