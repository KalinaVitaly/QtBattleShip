#include "Player.h"
#include <QDebug>

Player::Player() :
    ship1_count(0),
    ship2_count(0),
    ship3_count(0),
    ship4_count(0)
{
    initializationShip(ship1, 1, 1, max_ship1);
    initializationShip(ship2, 2, 2, max_ship2);
    initializationShip(ship3, 3, 3, max_ship3);
    initializationShip(ship4, 4, 4, max_ship4);

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            field[i][j] = 0;
}

const int Player::max_ship1 {4};
const int Player::max_ship2 {3};
const int Player::max_ship3 {2};
const int Player::max_ship4 {1};

int Player::getMaxShip1() const { return max_ship1; }
int Player::getMaxShip2() const { return max_ship2; }
int Player::getMaxShip3() const { return max_ship3; }
int Player::getMaxShip4() const { return max_ship4; }

bool Player::hasShipOnPosition(const QPair<int, int> &point)
{
    for(int i = 0; i < max_ship1; ++i)
        if (ship1[i]->isShipPoint(point))
            return true;

    for(int i = 0; i < max_ship2; ++i)
        if (ship2[i]->isShipPoint(point))
            return true;

    for(int i = 0; i < max_ship3; ++i)
        if (ship3[i]->isShipPoint(point))
            return true;

    for(int i = 0; i < max_ship4; ++i)
        if (ship4[i]->isShipPoint(point))
            return true;

    return false;
}

void Player::deleteShipFromPosition()
{

}

Ship*& Player::findShipOnField(const QPair<int, int> &point)
{
    for(int i = 0; i < max_ship1; ++i)
        if (ship1[i]->isShipPoint(point))
            return ship1[i];

    for(int i = 0; i < max_ship2; ++i)
        if (ship2[i]->isShipPoint(point))
            return ship2[i];

    for(int i = 0; i < max_ship3; ++i)
        if (ship3[i]->isShipPoint(point))
            return ship3[i];

    for(int i = 0; i < max_ship4; ++i)
        if (ship4[i]->isShipPoint(point))
            return ship4[i];

}

bool Player::checkHit(const QPair<int, int> &position)
{
    //change this function to small normal function
    for(int i = 0; i < max_ship1; ++i) {
        if (ship1[i]->isShipInjured(position))
            return true;
    }
    for(int i = 0; i < max_ship2; ++i){
        if (ship2[i]->isShipInjured(position))
            return true;
    }

    for(int i = 0; i < max_ship3; ++i){
        if (ship3[i]->isShipInjured(position))
            return true;
    }

    if(ship4[0]->isShipInjured(position))
        return true;
    return false;
}

Ship** Player::getShipByType(int type)
{
    if (type == 1)
        return ship1;
    else if (type == 2)
        return ship2;
    else if (type == 3)
        return ship3;
    else if (type == 4)
        return ship4;
}

int& Player::getByTypeShipCount(int type)
{
    if (type == 1)
        return ship1_count;
    else if (type == 2)
        return ship2_count;
    else if (type == 3)
        return ship3_count;
    else if (type == 4)
        return ship4_count;
}

int Player::getByTypeShipLength(int type)
{
    if (type == 1)
        return 1;
    else if (type == 2)
        return 2;
    else if (type == 3)
        return 3;
    else if (type == 4)
        return 4;
}

bool Player::canSetShipInThisPosition(int type, const QPair<int, int> &position, bool orientation)
{
    if (orientation) {
        if (position.first + getByTypeShipLength(type) > 10)
            return false;

        for(int i = 0; i < getByTypeShipLength(type); ++i) {
             if (field[position.second][position.first + i] == 1)
                 return false;
        }
    }
    else {
        if (position.second + getByTypeShipLength(type) > 10)
            return false;

        for(int i = 0; i < getByTypeShipLength(type); ++i)
             if (field[position.second + i][position.first] == 1)
                 return false;
    }
    return true;
}

void Player::deleteShipFromField(const QPair<int, int> &position, bool orientation, int deck_count)
{
    if (orientation) {
        for(int i = 0; i < deck_count; ++i)
             field[position.second][position.first + i] = 0;
    }
    else {
        for(int i = 0; i < deck_count; ++i)
             field[position.second + i][position.first] = 0;
    }
}

void Player::setNewShipPosition(Ship *ship, const QPair<int, int> &position, bool orientation)
{
    deleteShipFromField(position, orientation, ship->getShipDeckCount());

    if (orientation) {
        for(int i = 0; i < ship->getShipDeckCount(); ++i)
             field[position.second][position.first + i] = 1;
    }
    else {
        for(int i = 0; i < ship->getShipDeckCount(); ++i)
             field[position.second + i][position.first] = 1;
    }

    ship->setShipPosition(position, orientation);
}

void Player::setShipPositionInField(int type, const QPair<int, int> &position, bool orientation)
{
    if (orientation) {
        for(int i = 0; i < getByTypeShipLength(type); ++i)
             field[position.second][position.first + i] = 1;
    }
    else {
        for(int i = 0; i < getByTypeShipCount(type); ++i)
             field[position.second + i][position.first] = 1;
    }
}

void Player::setShipPosition(int type, const QPair<int, int> &position, bool orientation)
{
    int count = 0;
    Ship **choose_ship = nullptr;
    count = getByTypeShipCount(type);
    choose_ship = getShipByType(type);
    if (choose_ship != nullptr) {
        choose_ship[count]->setShipPosition(position, orientation);
        setShipPositionInField(type, position, orientation);
        ++count;
    }
    else {
        qDebug() << "Player::setShipPosition nullptr";
    }

}

void Player::initializationShip(Ship **ship, int ship_type, int deck_count, int count)
{
    for (int i = 0; i < count; ++i)
        ship[i] = new Ship(ship_type, deck_count);
}

Player::~Player()
{
    for(int i = 0; i < max_ship1; ++i)
        delete ship1[i];

    for(int i = 0; i < max_ship2; ++i)
        delete ship2[i];

    for(int i = 0; i < max_ship3; ++i)
        delete ship3[i];

    delete ship4[0];
}
