#ifndef AUTOMATICSHIPSPLACEMENT_H
#define AUTOMATICSHIPSPLACEMENT_H

#include "Player.h"
#include "GridButtonWidget.h"
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
    static void setRandomPositionShips(Player *_player);

signals:
    void shipsSet(int type);
};

#endif // AUTOMATICSHIPSPLACEMENT_H
