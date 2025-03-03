#include "include/Player.h"
#include "include/gameWorld.h"
#include "include/Monster.h"
#include <iostream>
#include <cstdlib>

int main()
{
    srand(time(NULL));
    gameWorld world;
    Player player;
    Monster monster;

    world.generateWorld(monster);
    world.printWorld(monster);
    player.playerMovement(world, monster);
    return 0;
}
