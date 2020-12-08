#include "Player.h"
#include <QDebug>

Player::Player()
{
    ships.insert(1, QVector<Ship *>(max_ship1));
    ships.insert(2, QVector<Ship *>(max_ship2));
    ships.insert(3, QVector<Ship *>(max_ship3));
    ships.insert(4, QVector<Ship *>(max_ship4));
    ships_count.insert(1, 0);
    ships_count.insert(2, 0);
    ships_count.insert(3, 0);
    ships_count.insert(4, 0);

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            field[i][j] = 0;
}

const int Player::max_ship1 {4};
const int Player::max_ship2 {3};
const int Player::max_ship3 {2};
const int Player::max_ship4 {1};

std::array<std::array<int, 10>, 10> Player::getField() { return field; }

int Player::getShipCount(int type) const {
    if (type < 1 || type > 4) {
        qDebug() << "Player::getShipCount: Index error";
        exit(1);
    }
    return ships_count[type];
}

void Player::deleteAllShips() {
    for (int i = 1; i <= 4; ++i) {
        for(int j = ships_count[i] - 1; j >= 0; --j) {
            QVector<QPair<int, int>> coordinates = ships[i][j]->getShipCoordinates();
            for (int k = 0; k < ships[i][j]->getShipDeckCount(); ++k) {
                field[coordinates[k].second][coordinates[k].first] = 0;
            }
            emit deleteShipFromFields(ships[i][j]->getShipCoordinates(), ships[i][j]->getOrientation());
            findAndDeleteShip(ships[i][j]);
        }
    }
}

void Player::DebugPrintField() {
    QString a = "";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; ++j) {
            a += QString::number(field[i][j]);
        }
        qDebug() << a;
        a = "";
    }
}

void Player::findAndDeleteShip(Ship * ship) {
    int type = ship->getShipType();
    int ship_index = ships[type].indexOf(ship);
    if (ship_index >= 0) {
        ships[type].swapItemsAt(ship_index, ships_count[ship->getShipType()] - 1);
        delete ship;
        --ships_count[ship->getShipType()];
    }
}

bool Player::hasShipOnPoint(const QPair<int, int> & point) const {
    for (int i = 1; i <= 4; ++i) {
        for(int j = 0; j < ships_count[i]; ++j) {
            if (ships[i][j]->isShipPoint(point))
                return true;
        }
    }
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
    ships[type][ships_count[type]] = new Ship;
    ships[type][ships_count[type]]->setShipPosition(ship_coordinates, type, orientation);
    ++ships_count[type];
}

bool Player::checkingPossiblePutInFrontOfTheVerticalShip(const QPair<int, int> &center) const {
    if (center.second - 1 >= 0) {
        if (field[center.second - 1][center.first] == 1) {
            //проверка перед кораблем
            return true;
        }
        if (center.first - 1 >= 0) {
            //проверка слева от корабля
            if (field[center.second - 1][center.first - 1] == 1) {
                return true;
            }
        }
        if (center.first + 1 < 10) {
            //проверка справа от корабля
            if (field[center.second - 1][center.first + 1] == 1) {
                return true;
            }
        }
    }
   return false;
}

bool Player::checkingPossiblePutInBackOfTheVerticalShip(const QPair<int, int> &center) const {
    if (center.second + 1 < 10) {
        if (field[center.second + 1][center.first] == 1) {
            //проверка перед кораблем
            return true;
        }
        if (center.first - 1 >= 0) {
            //проверка слева от корабля
            if (field[center.second + 1][center.first - 1] == 1) {
                return true;
            }
        }
        if (center.first + 1 < 10) {
            //проверка справа от корабля
            if (field[center.second + 1][center.first + 1] == 1) {
                return true;
            }
        }
    }
   return false;
}

bool Player::checkingPossiblePutInFrontOfTheHorizantalShip(const QPair<int, int> &center) const {
    if (center.first - 1 >= 0) {
        if (field[center.second][center.first - 1] == 1) {
            //проверка перед кораблем
            return true;
        }
        if (center.second - 1 >= 0) {
            //проверка слева от корабля
            if (field[center.second - 1][center.first - 1] == 1) {
                return true;
            }
        }
        if (center.second + 1 < 10) {
            //проверка справа от корабля
            if (field[center.second + 1][center.first - 1] == 1) {
                return true;
            }
        }
    }
    return false;
}

bool Player::checkingPossiblePutInBackOfTheHorizantalShip(const QPair<int, int> &center) const {
    if (center.first + 1 < 10) {
        if (field[center.second][center.first + 1] == 1) {
            //проверка перед кораблем
            return true;
        }
        if (center.second - 1 >= 0) {
            //проверка слева от корабля
            if (field[center.second - 1][center.first + 1] == 1) {
                return true;
            }
        }
        if (center.second + 1 < 10) {
            //проверка справа от корабля
            if (field[center.second + 1][center.first + 1] == 1) {
                return true;
            }
        }
    }
    return false;
}

bool Player::canSetShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates, bool orientation) {
    for (QPair<int, int> i : ship_coordinates)
        if (field[i.second][i.first] == 1 || i.second >= 10 || i.first >= 10)
            return false;

    if (orientation) {
        if (checkingPossiblePutInBackOfTheHorizantalShip(ship_coordinates[ship_coordinates.size() - 1]))
                return false;

        if (checkingPossiblePutInFrontOfTheHorizantalShip(ship_coordinates[0]))
                return false;

         for (QPair<int, int> i : ship_coordinates) {
             if ((i.second + 1 < 10 && field[i.second + 1][i.first] != 0) ||
                     (i.second - 1 >= 0 && field[i.second - 1][i.first] != 0))
                return false;
         }
    }
    else {
        if (checkingPossiblePutInBackOfTheVerticalShip(ship_coordinates[ship_coordinates.size() - 1]))
                return false;

        if (checkingPossiblePutInFrontOfTheVerticalShip(ship_coordinates[0]))
                return false;

        for (QPair<int, int> i : ship_coordinates)
            if ((i.first + 1 < 10 && field[i.second][i.first + 1] != 0) ||
                    (i.first - 1 >= 0 && field[i.second][i.first - 1] != 0))
               return false;
    }
    return true;
}

bool Player::checkingPointPresenceShip(const QPair<int, int> &point) const {
    //проверка не попал ли в какой-нибудь корабль
    for (int i = 1; i <= 4; ++i) {
        for(int j = 0; j < ships_count[i]; ++j) {
            if (ships[i][j]->isShipPoint(point))
                return true;
        }
    }
    return false;
}

Ship* Player::findShipByPosition(const QPair<int, int> & point) {
    //находим корабль по координате
    for (int i = 1; i <= 4; ++i) {
        for(int j = 0; j < ships_count[i]; ++j) {
            if (ships[i][j]->isShipPoint(point))
                return ships[i][j];
        }
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

Player::~Player() {
    for (auto i : ships) {
        for (int j = 0; j < i.size(); ++j) {
            delete i[j];
        }
    }
}
