#ifndef MONSTER_H
#define MONSTER_H
class gameWorld; // Vorwärtsdeklarieren

class Monster
{
    public:
        Monster();
        ~Monster();

        // Setter
        void increaseMonsterDifficulty(gameWorld& world);
        void decreaseMonsterHealth();

        // Getter
        int getMonsterDamage() const;
        int getMonsterHealth() const;

        // restliche Methoden
        void printMonsterStats();

    private:
        int m_monsterDamage;
        int m_monsterHealth;
};

#endif // MONSTER_H
