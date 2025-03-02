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

        // restliche Methoden
        void playerMovement(gameWorld& world);
        void printPlayerStats(gameWorld& world);

    private:
        int m_hitPoints;
        int m_relicPoints;
        int m_positionX;
        int m_positionY;
        void changePlayerPosition(char inputDirection, gameWorld& world);
};

#endif // PLAYER_H
