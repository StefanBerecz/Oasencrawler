#include "../include/Monster.h"
#include "../include/gameWorld.h"
#include <iostream>

// ANSI COLORS siehe gameWorld.cpp
#define COLOR_RESET "\033[0m"
#define RED "\033[1;91m"
#define GREEN "\033[1;92m"
#define BLUE "\033[1;94m"
#define YELLOW "\033[1;93m"

Monster::Monster()
{
    //ctor
    this->m_monsterDamage = 0;
    this->m_monsterHealth = 0;
}

void Monster::increaseMonsterDifficulty(gameWorld& world)
{
    this->m_monsterDamage++;
    this->m_monsterHealth = world.getStageCount();
}

void Monster::decreaseMonsterHealth()
{
    this->m_monsterHealth--;
}

int Monster::getMonsterDamage() const
{
    return this->m_monsterDamage;
}

int Monster::getMonsterHealth() const
{
    return this->m_monsterHealth;
}

void Monster::printMonsterStats()
{
    std::cout << RED   << "==================================" << COLOR_RESET << std::endl;
    std::cout << YELLOW << "         MONSTER STATS            " << COLOR_RESET << std::endl;
    std::cout << RED   << "==================================" << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Monster Damage: " << COLOR_RESET
              << RED << this->m_monsterDamage << COLOR_RESET << std::endl;

    std::cout << YELLOW << "Monster Health: " << COLOR_RESET
              << RED << this->m_monsterHealth << COLOR_RESET << std::endl;

    std::cout << RED   << "==================================" << COLOR_RESET << std::endl;
}
