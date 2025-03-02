#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class Player; // Vorwärtsdeklaration

class gameWorld
{
    public:
        gameWorld();
        ~gameWorld();
        void generateWorld();
        void printWorld();

        // Getter
        int getHeroPositionX() const;
        int getHeroPositionY() const;
        char getFieldType(int X, int Y) const;
        int getRelicCount() const;

        // Setter
        void setHeroPosition(int newX, int newY);
        void setEmptyField(int oldX, int oldY);

        // restliche Methoden
        void newFieldEffect(char fieldType, Player& player);

    private:
        char m_gameWorld[5][5];
        int m_relicCount; // Anzahl Relics bei Generation

        // Arten von Feldern
        char m_emptyField; // nichts passiert
        char m_dangerousField; // mit 1/6 wsl Verletzt
        char m_wellField; // ausruhen
        char m_relicField; // Relikt gefunden
        char m_heroField;  // Symbol für Held
        int m_heroPositionX;
        int m_heroPositionY;
};

#endif // GAMEWORLD_H
