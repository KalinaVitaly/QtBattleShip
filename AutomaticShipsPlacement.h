#ifndef AUTOMATICSHIPSPLACEMENT_H
#define AUTOMATICSHIPSPLACEMENT_H

#include "Player.h"
#include "GridWidget.h"
#include "ShipsWidget.h"

class AutomaticShipsPlacement
{
private:
    Player *player;
public:
    AutomaticShipsPlacement() = delete;

    static void setRandomPositionShips(Player *_player, GridWidget *&grid_widget, ShipsWidget *&ships_widget);
};

#endif // AUTOMATICSHIPSPLACEMENT_H
