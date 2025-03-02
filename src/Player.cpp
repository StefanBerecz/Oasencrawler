#include "../include/Player.h"
#include "../include/gameWorld.h"
#include <iostream>

// ANSI COLORS siehe gameWorld.cpp
#define COLOR_RESET "\033[0m"
#define RED "\033[1;91m"
#define GREEN "\033[1;92m"
#define BLUE "\033[1;94m"
#define YELLOW "\033[1;93m"

Player::Player()
{
    //ctor
    this->m_hitPoints = 5;
    this->m_relicPoints = 0;
}

Player::~Player()
{
    //dtor
}

int Player::getHeroHealth()
{
    return this->m_hitPoints;
}

// Neuer HP Wert
void Player::setHeroHealth(char plusOrMinus)
{
    if(plusOrMinus == 'p')
    {
        this->m_hitPoints++;
    }
    else if(plusOrMinus == 'm')
    {
        this->m_hitPoints--;
    }
}

void Player::increaseRelics()
{
    this->m_relicPoints++;
}

void Player::playerMovement(gameWorld& world)
{
    char inputDirection;
    while(1)
    {
        std::cout<<"Bewegen mit WASD, BEENDEN mit X"<<std::endl;
        std::cin>> inputDirection;
        inputDirection = std::tolower(inputDirection); // Kleinbuchstaben
        switch(inputDirection)
        {
            case 'w':
            case 'a':
            case 's':
            case 'd':
                std::cout << GREEN << "Move"<< COLOR_RESET <<std::endl;
                changePlayerPosition(inputDirection, world);
                break;
            case 'x':
                std::cout << BLUE << "Spiel beendet" << COLOR_RESET <<std::endl;
                return;
            default:
                std::cout << RED << "INVALID INPUT!" << COLOR_RESET <<std::endl;
        }
        world.printWorld();
        if(this->m_hitPoints <= 0)
        {
            system("clear");
            std::cout << RED << "YOU DIED" << COLOR_RESET <<std::endl;
            return;
        }
        if(this->m_relicPoints == world.getRelicCount())
        {
            system("clear");
            std::cout << YELLOW << "VICTORY ACHIEVED" << COLOR_RESET <<std::endl;
            return;
        }
    }
}

void Player::changePlayerPosition(char inputDirection, gameWorld& world)
{
    int currentHeroX = world.getHeroPositionX();
    int currentHeroY = world.getHeroPositionY();
    int newHeroX = currentHeroX;
    int newHeroY = currentHeroY;

    switch(inputDirection)
    {
        case 'w':
            if(currentHeroX > 0) newHeroX = currentHeroX - 1;
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
    world.setEmptyField(currentHeroX, currentHeroY); // Felder auf leer setzeb
    world.newFieldEffect(world.getFieldType(newHeroX, newHeroY), *this); // Effekt der neuen Position
    world.setHeroPosition(newHeroX, newHeroY); // Aktualisiert Spieler auf neue Position
}
