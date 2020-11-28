#ifndef AUTOMATICSHIPSPLACEMENT_H
#define AUTOMATICSHIPSPLACEMENT_H

#include "Player.h"

class AutomaticShipsPlacement
{
private:
    Player *player;
public:
    AutomaticShipsPlacement();

    void setPlayer(Player *_player);
    void setRandomPositionShips();
};

#endif // AUTOMATICSHIPSPLACEMENT_H
