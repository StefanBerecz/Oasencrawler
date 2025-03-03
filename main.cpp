#include "include/Player.h"
#include "include/gameWorld.h"
#include <iostream>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    gameWorld world;
    Player player;

    world.generateWorld();
    world.printWorld();
    player.playerMovement(world);
    return 0;
}
