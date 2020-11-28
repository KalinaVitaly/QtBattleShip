#include "AutomaticShipsPlacement.h"

AutomaticShipsPlacement::AutomaticShipsPlacement()
{

}

void AutomaticShipsPlacement::setPlayer(Player *_player) { player = _player; }

void AutomaticShipsPlacement::setRandomPositionShips()
{
    QPair<int, int> point;
    bool continue_set_ship_position = false;
    bool orientation;
    int type = 4;
    //int type_size[]

    for (int i = 1; i <= type; ++i)
    {
        //for(int j = 0; j < )
        while (continue_set_ship_position)
            if (player->canSetShipInThisPosition(type, point, orientation)) {
                player->setShipPosition(type, point, orientation);
                continue_set_ship_position = true;
            }

    }
}
