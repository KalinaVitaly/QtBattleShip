#include "Player.h"
#include <QDebug>

Player::Player() :
    ship1_count(0),
    ship2_count(0),
    ship1(max_ship1),
    ship2(max_ship2)
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            field[i][j] = 0;
}

const int Player::max_ship1 {4};
const int Player::max_ship2 {3};

int Player::getMaxShip1() const { return max_ship1; }

void Player::findAndDeleteShip(Ship * ship) {
    int pos = ship1.indexOf(ship);
    if (pos >= 0) {
        ship1.swapItemsAt(pos, ship1_count - 1);
        delete ship;
        --ship1_count;
    }

    pos = ship2.indexOf(ship);
    if (pos >= 0) {
        ship2.swapItemsAt(pos, ship2_count - 1);
        delete ship;
        --ship2_count;
    }

}

bool Player::hasShipOnPoint(const QPair<int, int> & point) const {
    for(int i = 0; i < ship1_count; ++i)
        if (ship1[i]->isShipPoint(point))
            return true;

    for(int i = 0; i < ship2_count; ++i)
        if (ship2[i]->isShipPoint(point))
            return true;

    return false;
}

void Player::deleteShipFromPosition(const QPair<int, int>& point) {
    Ship *ship = findShipByPosition(point);
    if (ship == nullptr) {
        qDebug() << "Player::deleteShipFromPosition() ship don't find!";
        exit(1);
    }
    else {
        QVector<QPair<int, int>> coordinates = ship->getShipCoordinates();
        for (int i = 0; i < ship->getShipDeckCount(); ++i) {
            field[coordinates[i].second][coordinates[i].first] = 0;
        }

        findAndDeleteShip(ship);
    }
}

QVector<QPair<int, int>> Player::convertPointAndOrientation2Coordinates(const QPair<int, int>& point, int type, bool orientation) {
    //Из точки и направления получаем вектор координат
    QVector<QPair<int, int>> ship_coordinates(type);
//    Ship *ship = findShipByPosition(point);
//    QPair<int, int> first_point = ship->getShipbegin();
    if (orientation) {
        for(int i = 0; i < type; ++i) {
             ship_coordinates[i] = qMakePair(point.first + i, point.second);
        }
    }
    else {
        for(int i = 0; i < type; ++i) {
             ship_coordinates[i] = qMakePair(point.first, point.second + i);
        }
    }
    return ship_coordinates;
}

void Player::setShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates, int type, bool orientation) {
    //Устанавливаем корабль на позицию на карте и добавляем в массив
    for (QPair<int, int> i : ship_coordinates){
        field[i.second][i.first] = 1;
    }
    if (type == 1) {
        ship1[ship1_count] = new Ship;
        ship1[ship1_count++]->setShipPosition(ship_coordinates, type, orientation);
    }
    else if (type == 2) {
        ship2[ship2_count] = new Ship;
        ship2[ship2_count++]->setShipPosition(ship_coordinates, type, orientation);
    }
}

bool Player::canSetShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates) {
    for (QPair<int, int> i : ship_coordinates)
        if (field[i.second][i.first] == 1 || i.second >= 10 || i.first >= 10)
            return false;
    return true;
}

bool Player::checkingPointPresenceShip(const QPair<int, int> &point) const {
    //проверка не попал ли в какой-нибудь корабль
    for(Ship* i : ship1)
        if (i->isShipPoint(point))
            return true;

    for(Ship* i : ship2)
        if (i->isShipPoint(point))
            return true;

    return false;
}

Ship* Player::findShipByPosition(const QPair<int, int> & point) {
    //находим корабль по координате
    qDebug() << "Ship1";
    for(int i = 0; i < ship1_count; ++i)
        if (ship1[i]->isShipPoint(point))
            return ship1[i];

    for(int i = 0; i < ship2_count; ++i)
        if (ship2[i]->isShipPoint(point)) {
            qDebug() << "Ship2";
            return ship2[i];
        }

    return nullptr;
}

void Player::setBombHitOnPoint(const QPair<int, int> &point) {
    //Установка попадания в корабль
    Ship *ship = findShipByPosition(point);
    if (ship != nullptr) {
        field[point.second][point.first] = 3;
        ship->isShipInjured(point);
    }
}
