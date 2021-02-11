#include "Ship.h"
#include <QDebug>

Ship::Ship() {}

int Ship::getTypeOfShip() const { return typeOfShip; }
int Ship::getShipDeckCount() const { return deckCount; }
bool Ship::getIsShipDestroyeded() const { return isShipDestroyeded; }
bool Ship::getOrientationOfShip() const { return  orientationOfShip; }
QPair<int, int> Ship::getShipBegin() { return ship_coordinates_and_deck_condition[0].first; }

QVector<QPair<int, int>> Ship::getShipCoordinates() {
    QVector<QPair<int, int>> coordinates(deckCount);
    for(int i = 0; i < deckCount; ++i) {
        coordinates[i] = ship_coordinates_and_deck_condition[i].first;
    }
    return coordinates;
}

bool Ship::isShipPoint(const QPair<int, int> &point)
{
    for(auto i : ship_coordinates_and_deck_condition)
        if (i.first == point)
            return true;
    return false;
}

void Ship::setShipPosition(const QVector<QPair<int, int>> &position, int _ship_type, bool _orientation)
{
    isShipDestroyeded = false;
    orientationOfShip = _orientation;
    typeOfShip = _ship_type;
    deckCount = position.size();
    QPair<QPair<int, int>, bool> node;
    for (QPair<int, int> i : position) {
        node.first = i;
        node.second = true;
        ship_coordinates_and_deck_condition.push_back(node);
    }
}

bool Ship::isShipInjured(const QPair<int, int> &point)
{
    for(int i = 0; i < deckCount; ++i)
        if(ship_coordinates_and_deck_condition[i].first.first == point.first &&
                ship_coordinates_and_deck_condition[i].first.second == point.second) {
             ship_coordinates_and_deck_condition[i].second = false;
             return true;
         }
    return false;
}
bool Ship::isShipDeath()
{
    for(int i = 0; i < deckCount; ++i)
         if(ship_coordinates_and_deck_condition[i].second)
             return false;

    isShipDestroyeded = true;
    return true;
}

