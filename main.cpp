#include <iostream>
#include <cstdlib>
#include "Room.h"

int main()
{
    srand(time(NULL));
    Room* room1 = new Room();
    room1->Display();
    //Entity* entity1 = new Entity();
    //std::cout << entity1->mDisplay << std::endl;
}
