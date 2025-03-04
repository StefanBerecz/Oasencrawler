#include "../include/gameWorld.h"
#include "../include/Player.h"
#include "../include/Monster.h"
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
#define MAGENTA "\033[1;95m" // 95 ist bright magenta = Relikte
#define WHITE "\033[1;97m" // 97 ist bright white = leeres Feld
#define YELLOW "\033[1;93m" // 93 ist bright yellow = Monster

gameWorld::gameWorld()
{
    //ctor
    this->m_emptyField    = 'E'; // "Empty"
    this->m_dangerousField= 'G'; // "Gefahr"
    this->m_wellField     = 'B'; // "Brunnen"
    this->m_relicField    = 'R'; // "Relikt"
    this->m_heroField     = '@'; // Spieler Symbol
    this->m_monsterField = 0; // Monster Symbol

    // Position des Spielers
    this->m_heroPositionX = 0;
    this->m_heroPositionY = 0;

    this->m_monsterPositionX = 3;
    this->m_monsterPositionY = 3;
    this->m_stageCount = 0;
    this->m_fightsThisRound = 0;
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

// Position des Monsters
int gameWorld::getMonsterPositionX() const
{
    return m_monsterPositionX;
}

int gameWorld::getMonsterPositionY() const
{
    return m_monsterPositionY;
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

// derzeitiges Stage-Level
int gameWorld::getStageCount() const
{
    return m_stageCount;
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

// Neue Monsterposition
void gameWorld::setMonsterPosition(int newX, int newY)
{
     if(newX < 0 || newX > 4 || newY < 0 || newY > 4)
    {
        std::cout << "Invalid Position" << std::endl;
        return;
    }
    this->m_monsterPositionX = newX;
    this->m_monsterPositionY = newY;
}

// Leert Feld
void gameWorld::setEmptyField(int oldX, int oldY)
{
    this->m_gameWorld[oldX][oldY] = this->m_emptyField;
}

// Resettet Anzahl der Fights
 void gameWorld::resetFightsThisRound()
 {
     this->m_fightsThisRound++;
 }

// Effekt des neuen Feldes
void gameWorld::newFieldEffect(char fieldType, Player& player)
{
    int chanceForOuch;
    switch(fieldType)
    {
        case 'G':
            chanceForOuch = rand() % 6 + 1;
            if(chanceForOuch == 1)
                player.saveRoll(); // Verlgeich mit Attributswert
            break;
        case 'B':
            player.findItem();
            player.setHeroHealth('p'); // p für Plus
            break;
        case 'R':
            player.increaseRelics();
            player.findItem();
            break;
        default:
            // zB bei empty field
            break;
    }
}

// Generiert Gameworld und füllt Felder
void gameWorld::generateWorld(Monster& monster)
{
    // Variable = rand() % 10 + 1; fuer Zahl zwischen 1 - 10
    int randomField;
    this->m_stageCount++;
    this->m_relicCount = 0;

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
                    if (!((i == this->m_heroPositionX && j == this->m_heroPositionY) ||
                          (i == this->m_monsterPositionX && j == this->m_monsterPositionY)))
                    {
                        this->m_gameWorld[i][j] = this->m_relicField; // weder Held noch Monster auf dem Feld
                        this->m_relicCount++;
                    }
                    break;
            }
        }
    }
    if(this->m_relicCount <= 0)
    {
        this->generateExtraRelic(); // Falls zu wenige Relikte
    }
    this->increaseDifficulty(monster);
}

void gameWorld::generateExtraRelic()
{
    int heroX = this->getHeroPositionX();
    int heroY = this->getHeroPositionY();
    int monsterX = this->getMonsterPositionX();
    int monsterY = this->getMonsterPositionY();
    int x = 0;
    int y = 0;
    while((x == heroX && y == heroY) || (x == monsterX && y == monsterY)) // Damit Relikt nicht selbe Position wie Held oder Monster
    {
        x = rand() % 5;
        y = rand() % 5;
    }
    this->m_gameWorld[y][x] = this->m_relicField;
    this->m_relicCount = 1;
}

// Schwierigkeitsgrad erhöhen
void gameWorld::increaseDifficulty(Monster& monster)
{
    monster.increaseMonsterDifficulty(*this);
    this->m_monsterField++;
}

// Generiert neue Stage
void gameWorld::newStage(Player& player, Monster& monster)
{
    system("clear");
    this->generateWorld(monster);
    this->printWorld(monster);
    player.resetRelicPointsStage();
}


// Printet Gameworld in Konsole
void gameWorld::printWorld(Monster& monster)
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
            else if(i == this->getMonsterPositionX() && j == this->getMonsterPositionY() && (monster.getMonsterHealth() > 0))
            {
                std::cout << YELLOW << this->m_monsterField << COLOR_RESET;
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

void gameWorld::changePlayerPosition(char inputDirection, Player& player, Monster& monster)
{
    int currentHeroX = this->getHeroPositionX();
    int currentHeroY = this->getHeroPositionY();
    int newHeroX = currentHeroX;
    int newHeroY = currentHeroY;

    switch(inputDirection)
    {
        case 'w':
            if (currentHeroX > 0) newHeroX = currentHeroX - 1;
            break;
        case 'a':
            if (currentHeroY > 0) newHeroY = currentHeroY - 1;
            break;
        case 's':
            if (currentHeroX < 4) newHeroX = currentHeroX + 1;
            break;
        case 'd':
            if (currentHeroY < 4) newHeroY = currentHeroY + 1;
            break;
    }
    //Prüfen ob Held auf Monsterfeld geht
    if(newHeroX == this->m_monsterPositionX && newHeroY == this->m_monsterPositionY && (monster.getMonsterHealth() >= 1))
    {
        this->heroMonsterEpicClash(player, monster);
        return;
    }
    this->setEmptyField(currentHeroX, currentHeroY); // Felder auf leer setzen
    this->newFieldEffect(this->getFieldType(newHeroX, newHeroY), player); // Effekt der neuen Position
    this->setHeroPosition(newHeroX, newHeroY); // Aktualisiert Spieler auf neue Position
    this->changeMonsterPosition(player, monster); // Bewegt das Monster
}

void gameWorld::heroMonsterEpicClash(Player& player, Monster& monster)
{
    if(this->m_fightsThisRound == 1 || (monster.getMonsterHealth() < 1))
        return;
//    std::cout << RED << "Das Monster schmeckt Aua" << COLOR_RESET << std::endl;
    for(int i = 0; i < monster.getMonsterDamage(); i++)
    {
        player.setHeroHealth('m');
    }
    for(int i = 0; i < player.getStrength(); i++)
    {
        monster.decreaseMonsterHealth();
    }
    this->m_fightsThisRound = 1;
}

void gameWorld::changeMonsterPosition(Player& player, Monster& monster)
{
    if(monster.getMonsterHealth() < 1)
        return;

    int currentMonsterX = this->getMonsterPositionX();
    int currentMonsterY = this->getMonsterPositionY();
    int newMonsterX = currentMonsterX;
    int newMonsterY = currentMonsterY;

    int randomDirection = rand() % 4 +1;
    switch(randomDirection)
    {
        case 1:
            if(currentMonsterX > 0) newMonsterX = currentMonsterX - 1;
            break;
        case 2:
            if (currentMonsterY > 0) newMonsterY = currentMonsterY - 1;
            break;
        case 3:
            if (currentMonsterX < 4) newMonsterX = currentMonsterX + 1;
            break;
        case 4:
            if (currentMonsterY < 4) newMonsterY = currentMonsterY + 1;
            break;
    }
     if(newMonsterX == this->m_heroPositionX && newMonsterY == this->m_heroPositionY)
    {
        this->heroMonsterEpicClash(player, monster);
        return;
    }
    this->setMonsterPosition(newMonsterX, newMonsterY); // Aktualisiert Monster  auf neue Position
}
