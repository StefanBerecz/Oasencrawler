#include "../include/Player.h"
#include "../include/gameWorld.h"
#include "../include/Monster.h"
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
    this->m_relicPointsTotal = 0;
    this->m_relicPointsStage = 0;
    this->m_attackValue = 1;
}

Player::~Player()
{
    //dtor
}

int Player::getHeroHealth()
{
    return this->m_hitPoints;
}

int Player::getHeroRelicPoints()
{
    return this->m_relicPointsTotal;
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
    this->m_relicPointsTotal++;
    this->m_relicPointsStage++;
    this->m_attackValue++;
}

void Player::resetRelicPointsStage()
{
    this->m_relicPointsStage = 0;
}

void Player::playerMovement(gameWorld& world, Monster& monster)
{
    char inputDirection;
    while(1)
    {
        this->printPlayerStats(world);
        monster.printMonsterStats();
        world.resetFightsThisRound();
        std::cout<<"Bewegen mit WASD, BEENDEN mit X"<<std::endl;
        std::cin>> inputDirection;
        inputDirection = std::tolower(inputDirection); // Kleinbuchstaben
        switch(inputDirection)
        {
            case 'w':
            case 'a':
            case 's':
            case 'd':
                world.changePlayerPosition(inputDirection, *this, monster); // verändert auch Position des Monsters
                break;
            case 'x':
                system("clear");
                std::cout << BLUE << "         Spiel beendet" << COLOR_RESET <<std::endl;
                this->printPlayerStats(world);
                monster.printMonsterStats();
                return;
            default:
                std::cout << RED << "INVALID INPUT!" << COLOR_RESET <<std::endl;
        }
        world.printWorld(monster);
        if(this->m_hitPoints <= 0)
        {
            system("clear");
            std::cout << RED << "            YOU DIED" << COLOR_RESET <<std::endl;
            std::cout << std::endl;
            this->printPlayerStats(world);
            monster.printMonsterStats();
            return;
        }
        if(this->m_relicPointsStage == world.getRelicCount())
            world.newStage(*this, monster);
    }
}

void Player::printPlayerStats(gameWorld& world)
{
    std::cout << BLUE   << "==================================" << COLOR_RESET << std::endl;
    std::cout << GREEN  << "         PLAYER STATS             " << COLOR_RESET << std::endl;
    std::cout << BLUE   << "==================================" << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Current stage: " << COLOR_RESET
              << GREEN << world.getStageCount() << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Health: " << COLOR_RESET;
    if(m_hitPoints <= 2)
        std::cout << RED;
    else
        std::cout << GREEN;
    std::cout << m_hitPoints << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Attack value: " << COLOR_RESET
              << GREEN << this->m_attackValue << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Relics Collected This Stage: " << COLOR_RESET
              << GREEN << m_relicPointsStage << "/"<< world.getRelicCount() << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Relics Collected Total: " << COLOR_RESET
              << GREEN << m_relicPointsTotal << COLOR_RESET << std::endl;

    std::cout << BLUE   << "==================================" << COLOR_RESET << std::endl;
}
