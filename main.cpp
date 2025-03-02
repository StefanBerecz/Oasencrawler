#include "include/Player.h"
#include "include/gameWorld.h"
#include <iostream>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    gameWorld world;
    world.generateWorld();
    world.printWorld();

    Player player;
    player.playerMovement(world);

    //player.printstats();
    return 0;
}
