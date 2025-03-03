#ifndef PLAYER_H
#define PLAYER_H

class gameWorld; // Vorwärtsdeklaration

class Player
{
    public:
        Player();
        ~Player();

        // Getter
        int getHeroHealth();

        // Setter
        void setHeroHealth(char plusOrMinus); // Plus & Minus
        void increaseRelics();
        void resetRelicPointsStage();

        // restliche Methoden
        void playerMovement(gameWorld& world);
        void printPlayerStats(gameWorld& world);

    private:
        int m_hitPoints;
        int m_relicPointsTotal;
        int m_relicPointsStage;
        int m_attackValue; // entspricht relicPointsTotal
        int m_positionX;
        int m_positionY;
};

#endif // PLAYER_H
