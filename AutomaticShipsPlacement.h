#ifndef AUTOMATICSHIPSPLACEMENT_H
#define AUTOMATICSHIPSPLACEMENT_H

#include "Player.h"
#include "GridWidget.h"
#include "ShipsWidget.h"
#include <ctime>
#include <random>

class AutomaticShipsPlacement
{
private:
    Player *player;
public:
    AutomaticShipsPlacement() = delete;

    static void setRandomPositionShips(Player *_player, GridWidget *&grid_widget, ShipsWidget *&ships_widget);

signals:
    void shipsSet(int type);
};

#endif // AUTOMATICSHIPSPLACEMENT_H
