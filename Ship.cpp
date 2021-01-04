#include "Ship.h"
#include <QDebug>

Ship::Ship() {}

int Ship::getShipType() const { return ship_type; }
int Ship::getShipDeckCount() const { return deck_count; }
bool Ship::getIsShipDestroyed() const { return is_ship_destroyed; }
bool Ship::getOrientation() const { return  orientation; }
QPair<int, int> Ship::getShipbegin() { return ship_coordinates_and_deck_condition[0].first; }

QVector<QPair<int, int>> Ship::getShipCoordinates() {
    QVector<QPair<int, int>> coordinates(deck_count);
    for(int i = 0; i < deck_count; ++i) {
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
    is_ship_destroyed = false;
    orientation = _orientation;
    ship_type = _ship_type;
    deck_count = position.size();
    QPair<QPair<int, int>, bool> node;
    for (QPair<int, int> i : position) {
        node.first = i;
        node.second = true;
        ship_coordinates_and_deck_condition.push_back(node);
    }
}

bool Ship::isShipInjured(const QPair<int, int> &point)
{
    for(int i = 0; i < deck_count; ++i)
        if(ship_coordinates_and_deck_condition[i].first.first == point.first &&
                ship_coordinates_and_deck_condition[i].first.second == point.second) {
             ship_coordinates_and_deck_condition[i].second = false;
             return true;
         }
    return false;
}
bool Ship::isShipDeath()
{
    for(int i = 0; i < deck_count; ++i)
         if(ship_coordinates_and_deck_condition[i].second)
             return false;

    is_ship_destroyed = true;
    return true;
}

