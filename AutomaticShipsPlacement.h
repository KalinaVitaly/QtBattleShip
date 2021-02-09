#ifndef AUTOMATICSHIPSPLACEMENT_H
#define AUTOMATICSHIPSPLACEMENT_H

#include "Player.h"
#include "GridButtonWidget.h"
#include "ShipsWidget.h"
#include <ctime>
#include <random>

class AutomaticShipsPlacement
{
public:
    AutomaticShipsPlacement() = delete;

    //
    // Автоматически расставляет корабли в соотвествии с правилами игры
    //
    static void setRandomPositionShips(Player *_player, GridWidget *&grid_widget, ShipsWidget *&ships_widget);
    static void setRandomPositionShips(Player *_player);
};

#endif // AUTOMATICSHIPSPLACEMENT_H
