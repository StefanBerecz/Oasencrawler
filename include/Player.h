#ifndef PLAYER_H
#define PLAYER_H

class gameWorld; // Vorwärtsdeklaration
class Monster;

class Player
{
    public:
        Player();
        ~Player();

        // Getter
        int getHeroHealth();
        int getHeroRelicPoints();
        int getAgility();
        int getIntelligence();
        int getStrength();

        // Setter
        void setHeroHealth(char plusOrMinus); // Plus & Minus
        void increaseRelics();
        void resetRelicPointsStage();
        void findItem();

        // restliche Methoden
        void saveRoll();
        void playerMovement(gameWorld& world, Monster& monster);
        void printPlayerStats(gameWorld& world);

    private:
        int m_hitPoints;
        int m_relicPointsTotal;
        int m_relicPointsStage;

        // Attribute (können sinken)
        int m_agility;
        int m_intelligence;
        int m_strength;
};

#endif // PLAYER_H
