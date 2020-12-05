#include "AutomaticShipsPlacement.h"

void AutomaticShipsPlacement::setRandomPositionShips(Player *_player, GridWidget *&grid_widget, ShipsWidget *&ships_widget) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    QMap<int, int> max_ships;
    QPair<int, int> point;
    QVector<QPair<int, int>> coordinates;
    bool orientation;

    max_ships[1] = 4;
    max_ships[2] = 3;
    max_ships[3] = 2;
    max_ships[4] = 1;

    for (int i = 1; i <= 4; ++i) {
        for (int j = _player->getShipCount(i); j < max_ships[i]; ++j) {

            do {
                orientation = mersenne() % 2 == 1 ? true : false;
                point.first = mersenne() % 10;
                point.second = mersenne() % 10;
                coordinates = _player->convertPointAndOrientation2Coordinates(point, i, orientation);
            } while (!_player->canSetShipOnPosition(coordinates));
            _player->setShipOnPosition(coordinates, i, orientation);
            grid_widget->setShipPositionInGrid(point, orientation, i);
            ships_widget->setChooseShipType(i);
            ships_widget->changeDigitPixMap();
        }
    }
}
