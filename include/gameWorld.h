#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class Player; // Vorwärtsdeklaration
class Monster;

class gameWorld
{
    public:
        gameWorld();
        ~gameWorld();
        void generateWorld(Monster& monster);
        void printWorld(Monster& monster);

        // Getter
        int getHeroPositionX() const;
        int getHeroPositionY() const;
        int getMonsterPositionX() const;
        int getMonsterPositionY() const;
        char getFieldType(int X, int Y) const;
        int getRelicCount() const;
        int getStageCount() const;

        // Setter
        void setHeroPosition(int newX, int newY);
        void setMonsterPosition(int newX, int newY);
        void setEmptyField(int oldX, int oldY);
        void newStage(Player& player, Monster& monster);
        void resetFightsThisRound();

        // restliche Methoden
        void newFieldEffect(char fieldType, Player& player);
        void generateExtraRelic();
        void changePlayerPosition(char inputDirection, Player& player, Monster& monster);
        void changeMonsterPosition(Player& player, Monster& monster);
        void increaseDifficulty(Monster& monster);
        void heroMonsterEpicClash(Player& player, Monster& monster);

    private:
        char m_gameWorld[5][5];
        int m_relicCount; // Anzahl Relics bei Generation
        int m_heroPositionX;
        int m_heroPositionY;
        int m_monsterPositionX;
        int m_monsterPositionY;
        int m_stageCount;
        int m_fightsThisRound; // relevant damit nicht 2 Kämpfe in selber Runde

        // Arten von Feldern
        char m_emptyField; // nichts passiert
        char m_dangerousField; // mit 1/6 wsl Verletzt
        char m_wellField; // ausruhen
        char m_relicField; // Relikt gefunden
        char m_heroField;  // Symbol für Held
        int m_monsterField; // Symbol für Monster
};

#endif // GAMEWORLD_H
