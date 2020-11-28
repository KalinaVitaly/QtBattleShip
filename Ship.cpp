#include "Ship.h"
#include <QDebug>

Ship::Ship(int ship_type, int deck_count) :
    ship_type(ship_type),
    deck_count(deck_count)
{}

int Ship::getShipType() const { return ship_type; }
int Ship::getShipDeckCount() const { return deck_count; }
bool Ship::getIsShipDestroyed() const { return is_ship_destroyed; }

bool Ship::isShipPoint(const QPair<int, int> &point)
{
    for(auto i : ship_coordinates_and_deck_condition)
        if (i.first == point)
            return true;
    return false;
}

void Ship::setShipPosition(const QPair<int, int> &point, bool orientation)
{
    if (orientation) {
        for(int i = 0; i < deck_count; ++i) {
             ship_coordinates_and_deck_condition.append(qMakePair(qMakePair(point.first + i, point.second), true));
             qDebug() << point.first + i << " " << point.second;
        }
    }
    else {
        for(int i = 0; i < deck_count; ++i)
             ship_coordinates_and_deck_condition.append(qMakePair(qMakePair(point.first, point.second + i), true));
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
         if(ship_coordinates_and_deck_condition[i].second == true)
             return false;
    is_ship_destroyed = true;
    return true;
}

