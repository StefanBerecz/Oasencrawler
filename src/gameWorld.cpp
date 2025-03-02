#include "../include/gameWorld.h"
#include "../include/Player.h"
#include <cstdlib> // für rand()
#include <stdlib.h> // für system("clear")
#include <iostream>

// ANSI Codes
//Codes von https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
// \033 ist Octal Escape Sequence
// [ ist Control Sequence Introducer

// 0m resetet alle Modi
#define COLOR_RESET "\033[0m"

// 1; ....m setzt auf bold
#define RED "\033[1;91m" // 91 ist bright red = Gefahr
#define GREEN "\033[1;92m" // 92 ist bright green = Held
#define BLUE "\033[1;94m" // 94 ist bright blue = Brunnen
#define MAGENTA "\033[1;95m" // 95 ist bright magenta = relikte
#define WHITE "\033[1;97m" // 97 ist bright weiss = leeres Feld

gameWorld::gameWorld()
{
    //ctor
    this->m_emptyField    = 'E'; // "Empty"
    this->m_dangerousField= 'G'; // "Gefahr"
    this->m_wellField     = 'B'; // "Brunnen"
    this->m_relicField    = 'R'; // "Relikt"
    this->m_heroField     = '@'; // Spieler Symbol

    // Position des Spielers
    this->m_heroPositionX = 0;
    this->m_heroPositionY = 0;
}

gameWorld::~gameWorld()
{
    //dtor
}

// Position des Helden
int gameWorld::getHeroPositionX() const
{
    return m_heroPositionX;
}

int gameWorld::getHeroPositionY() const
{
    return m_heroPositionY;
}

// Art eines Feldes
char gameWorld::getFieldType(int X, int Y) const
{
    return m_gameWorld[X][Y];
}

// Anzahl Relics bei Generation
int gameWorld::getRelicCount() const
{
    return m_relicCount;
}


// Neue Spielerposition
void gameWorld::setHeroPosition(int newX, int newY)
{
    if(newX < 0 || newX > 4 || newY < 0 || newY > 4)
    {
        std::cout << "Invalid Position" << std::endl;
        return;
    }
    this->m_heroPositionX = newX;
    this->m_heroPositionY = newY;
}

// Leert Feld
void gameWorld::setEmptyField(int oldX, int oldY)
{
    this->m_gameWorld[oldX][oldY] = this->m_emptyField;
}

// Effekt des neuen Feldes
void gameWorld::newFieldEffect(char fieldType, Player& player)
{
    char healthEffect; // p für Plus, m für Minus
    int chanceForOuch;
    switch(fieldType)
    {
        case 'G':
            chanceForOuch = rand() % 6 + 1;
            healthEffect = 'm';
            if(chanceForOuch == 1) player.setHeroHealth(healthEffect);
            break;
        case 'B':
            healthEffect = 'p';
            player.setHeroHealth(healthEffect);
            break;
        case 'R':
            player.increaseRelics();
            break;
        default:
            // zB bei empty field
            break;
    }
}

// Generiert Gameworld und füllt Felder
void gameWorld::generateWorld()
{
    // Variable = rand() % 10 + 1; fuer Zahl zwischen 1 - 10
    int randomField;

    // Initialisiere Array und ordne Symbole zu
    for (int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            randomField = rand() % 10 + 1;
            switch(randomField)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    // Leeres Feld
                    this->m_gameWorld[i][j] = this->m_emptyField;
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                    // Gefahren Feld
                    this->m_gameWorld[i][j] = this->m_dangerousField;
                    break;
                case 9:
                    // Brunnen Feld
                    this->m_gameWorld[i][j] = this->m_wellField;
                    break;
                case 10:
                    // Relikt Feld
                    this->m_gameWorld[i][j] = this->m_relicField;
                    if(i != 0 || j != 0)
                        this->m_relicCount++; // Sonst kann auf 0,0 Relikt sein
                    break;
            }
        }
    }
    if(this->m_relicCount == 0)
        this->m_gameWorld[4][4] = this->m_relicField;
}

// Printet Gameworld in Konsole
void gameWorld::printWorld()
{
    system("clear"); // cleart die Konsole
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if(i == this->getHeroPositionX() && j == this->getHeroPositionY())
            {
                std::cout << GREEN << this->m_heroField << COLOR_RESET;
            }
            else
            {
                // Farbe abhängig von Feldtyp
                char field = this->m_gameWorld[i][j];
                switch(field)
                {
                    case 'E': // Leeres Feld
                        std::cout << WHITE << field << COLOR_RESET;
                        break;
                    case 'G': // Gefahren Feld
                        std::cout << RED << field << COLOR_RESET;
                        break;
                    case 'B': // Brunnen Feld
                        std::cout << BLUE << field << COLOR_RESET;
                        break;
                    case 'R': // Relikt Feld
                        std::cout << MAGENTA << field << COLOR_RESET;
                        break;
                    default:
                        break;
                }
            }
        }
        std::cout << std::endl;
    }
}
