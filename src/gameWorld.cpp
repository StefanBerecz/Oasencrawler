#include "gameWorld.h"

gameWorld::gameWorld()
{
    //ctor
}

gameWorld::~gameWorld()
{
    //dtor
}

// generates new Game World / fills array
void gameWorld::generateWorld()
{
    // Variable = rand() % 10 + 1
    // fuer Zahl zwischen 1 - 10
    int randomField;
    for (int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; i++)
        {
            randomField = rand() % 10 + 1;
            switch(randomField)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    //Leer == '' welches
                    gameWorld.m_fieldtype = Symbol eintragen ?;
                    gameWorld.m_gameWorld[i][j] = gameWorld.
                    break;case 5:s
                case 5:
                case 6:
                case 7:
                case 8:
                    // Gefahr == 'g'
                    break;
                case 9:
                    // Brunnen == 'b'
                    break;
                case 10:
                    // Relikt == 'r'
                    break;

            }
            this->m_gameWorld[i][j] = '-';
        }
    }

    // Player mit @
}
