#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();
        ~Player();

    private:
        int m_hitPoints;
        int m_relicPoints;
        int m_positionX;
        int m_positionY;
};

#endif // PLAYER_H
