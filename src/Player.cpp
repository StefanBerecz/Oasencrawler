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
    this->m_strength = 1;
    this->m_intelligence = 0;
    this->m_agility = 0;
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

int Player::getAgility()
{
    return this->m_agility;
}

int Player::getIntelligence()
{
    return this->m_intelligence;
}

int Player::getStrength()
{
    return this->m_strength;
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
}

void Player::findItem()
{
    int itemType = rand() % 3 + 1;
    switch(itemType)
    {
        case 1:
            // Agility
            this->m_agility++;
            break;
        case 2:
            // Intelligence
            this->m_intelligence++;
            break;
        case 3:
            // Strength
            this->m_strength++;
            break;
    }
}

void Player::resetRelicPointsStage()
{
    this->m_relicPointsStage = 0;
}

void Player::saveRoll()
{
    int attributeType = rand() % 3 + 1;
    switch(attributeType)
    {
        case 1:
            // Agility
            if(this->getAgility() < 1)
                this->setHeroHealth('m');
            else
                this->m_agility--;
            break;
        case 2:
            // Intelligence
            if(this->getIntelligence() < 1)
                this->setHeroHealth('m');
            else
                this->m_intelligence--;
            break;
        case 3:
            // Strength
            if(this->getStrength() < 1)
                this->setHeroHealth('m');
            else
                this->m_strength--;
            break;
    }
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

    std::cout << YELLOW << "Potions of Strength: " << COLOR_RESET
              << GREEN << this->m_strength << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Potions of Agility: " << COLOR_RESET
              << GREEN << this->m_agility << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Potions of Intelligence: " << COLOR_RESET
              << GREEN << this->m_intelligence << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Relics Collected This Stage: " << COLOR_RESET
              << GREEN << m_relicPointsStage << "/"<< world.getRelicCount() << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Relics Collected Total: " << COLOR_RESET
              << GREEN << m_relicPointsTotal << COLOR_RESET << std::endl;

    std::cout << BLUE   << "==================================" << COLOR_RESET << std::endl;
}
