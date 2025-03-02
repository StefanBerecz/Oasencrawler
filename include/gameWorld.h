#ifndef GAMEWORLD_H
#define GAMEWORLD_H


class gameWorld
{
    public:
        gameWorld();
        ~gameWorld();
        void generateWorld();

    private:
        char m_gameWorld[5][5];
        char m_fieldType; //vll Art des Feldes
            Symbole eintragen
            // leeres Feld
            // Gefahren
            // Brunnen
            // Relikte


};

#endif // GAMEWORLD_H
