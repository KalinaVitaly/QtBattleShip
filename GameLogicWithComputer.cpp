#include "GameLogicWithComputer.h"
#include <QDebug>

GameLogicWithComputer::GameLogicWithComputer(Player *player, QObject *parent) : QObject(parent),
                                        player1(player),
                                        turn(rand() % 2)
{
    computer = new ComputerPlayer;
    player2 = new Player;

    AutomaticShipsPlacement::setRandomPositionShips(player2);
}

void GameLogicWithComputer::gameCycle() {

}

QVector<QPair<int, int>> GameLogicWithComputer::fieldsCoordinatesAroundDestroyededShip(Player *player, const QVector<QPair<int, int>> & ship_coordinates, bool orientation) {
    QVector<QPair<int, int>> fields_around_ship;
    //разбить на части
    if (orientation) {
        //горизонтальный корабль
        if (ship_coordinates[0].first - 1 >= 0) {
            //поля перед кораблем
            if (player->getField()[ship_coordinates[0].second][ship_coordinates[0].first - 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[0].first - 1, ship_coordinates[0].second));
                player->getField()[ship_coordinates[0].second][ship_coordinates[0].first - 1] = 4;
            }

            if (ship_coordinates[0].second - 1 >= 0 &&
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first - 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[0].first - 1, ship_coordinates[0].second - 1));
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first - 1] = 4;
            }

            if (ship_coordinates[0].second + 1 < 10 &&
                player->getField()[ship_coordinates[0].second + 1][ship_coordinates[0].first - 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[0].first - 1, ship_coordinates[0].second + 1));
                player->getField()[ship_coordinates[0].second + 1][ship_coordinates[0].first - 1] = 4;
            }
        }

        if (ship_coordinates[ship_coordinates.size() - 1].first + 1 < 10) {
            //поля сзади корабля
            if (player->getField()[ship_coordinates[ship_coordinates.size() - 1].second][ship_coordinates[ship_coordinates.size() - 1].first + 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[ship_coordinates.size() - 1].first + 1, ship_coordinates[ship_coordinates.size() - 1].second));
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second][ship_coordinates[ship_coordinates.size() - 1].first + 1] = 4;
            }

            if (ship_coordinates[ship_coordinates.size() - 1].second - 1 >= 0 &&
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second - 1][ship_coordinates[ship_coordinates.size() - 1].first + 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[ship_coordinates.size() - 1].first + 1, ship_coordinates[ship_coordinates.size() - 1].second - 1));
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second - 1][ship_coordinates[ship_coordinates.size() - 1].first + 1] = 4;
            }

            if (ship_coordinates[ship_coordinates.size() - 1].second + 1 < 10 &&
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first + 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[ship_coordinates.size() - 1].first + 1, ship_coordinates[ship_coordinates.size() - 1].second + 1));
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first + 1] = 4;
            }
        }

        //боковые поля
        for (int i = 0; i < ship_coordinates.size(); ++i) {
            if (ship_coordinates[i].second + 1 < 10 && player->getField()[ship_coordinates[i].second + 1][ship_coordinates[i].first] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[i].first, ship_coordinates[i].second + 1));
                player->getField()[ship_coordinates[i].second + 1][ship_coordinates[i].first] = 4;
            }

            if (ship_coordinates[i].second - 1 >= 0 && player->getField()[ship_coordinates[i].second - 1][ship_coordinates[i].first] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[i].first, ship_coordinates[i].second - 1));
                player->getField()[ship_coordinates[i].second - 1][ship_coordinates[i].first] = 4;
            }
        }
    }
    else {
        //вертикальный корабль
        if (ship_coordinates[0].second - 1 >= 0) {
            //поля перед кораблем
            if (player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[0].first, ship_coordinates[0].second - 1));
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first] = 4;
            }

            if (ship_coordinates[0].first - 1 >= 0 &&
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first - 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[0].first - 1, ship_coordinates[0].second - 1));
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first - 1] = 4;
            }

            if (ship_coordinates[0].first + 1 < 10 &&
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first + 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[0].first + 1, ship_coordinates[0].second - 1));
                player->getField()[ship_coordinates[0].second - 1][ship_coordinates[0].first + 1] = 4;
            }
        }

        if (ship_coordinates[ship_coordinates.size() - 1].second + 1 < 10) {
            //поля сзади корабля
            if (player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[ship_coordinates.size() - 1].first, ship_coordinates[ship_coordinates.size() - 1].second + 1));
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first] = 4;
            }

            if (ship_coordinates[ship_coordinates.size() - 1].first - 1 >= 0 &&
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first - 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[ship_coordinates.size() - 1].first - 1, ship_coordinates[ship_coordinates.size() - 1].second + 1));
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first - 1] = 4;
            }

            if (ship_coordinates[ship_coordinates.size() - 1].first + 1 < 10 &&
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first + 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[ship_coordinates.size() - 1].first + 1, ship_coordinates[ship_coordinates.size() - 1].second + 1));
                player->getField()[ship_coordinates[ship_coordinates.size() - 1].second + 1][ship_coordinates[ship_coordinates.size() - 1].first + 1] = 4;
            }
        }

        for (int i = 0; i < ship_coordinates.size(); ++i) {
            if (ship_coordinates[i].first + 1 < 10 && player->getField()[ship_coordinates[i].second][ship_coordinates[i].first + 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[i].first + 1, ship_coordinates[i].second));
                player->getField()[ship_coordinates[i].second][ship_coordinates[i].first + 1] = 4;
            }

            if (ship_coordinates[i].first - 1 >= 0 && player->getField()[ship_coordinates[i].second][ship_coordinates[i].first - 1] == 0) {
                fields_around_ship.push_back(QPair<int, int>(ship_coordinates[i].first - 1, ship_coordinates[i].second));
                player->getField()[ship_coordinates[i].second][ship_coordinates[i].first - 1] = 4;
            }
        }
    }
    return fields_around_ship;
}

void GameLogicWithComputer::shootFromComputer() {
    QPair<int, int> coordinate = computer->Shooting();
    last_shoot = coordinate;

    if (player1->hasShipOnPoint(coordinate)) {
        player1->setBombHitOnPoint(coordinate);

        if (player1->isShipDestroyed(coordinate)) {
            QVector<QPair<int, int>> fields_around_ship = fieldsCoordinatesAroundDestroyededShip(player1,
                player1->getShipCoordinate(coordinate), player1->getShipOrientation(coordinate));
            player1->DebugPrintField();
            emit setAroundDestroyededPlayerShipFields(fields_around_ship);
        }
        else {

        }
        emit setComputerBombHit(coordinate);
    }
    else {
        player1->setBombHitOnPoint(coordinate);
        emit setComputerBombMiss(coordinate);
    }
}

void GameLogicWithComputer::setShootFromGrid(const QPair<int, int> & coordinate) {
    if (player2->hasShipOnPoint(coordinate)) {
        player2->setBombHitOnPoint(coordinate);
        if (player2->isShipDestroyed(coordinate)) {
            QVector<QPair<int, int>> fields_around_ship = fieldsCoordinatesAroundDestroyededShip(player2,
                player2->getShipCoordinate(coordinate), player2->getShipOrientation(coordinate));
            setAroundDestroyededShipInactiveFields(fields_around_ship);
        }
        emit setBombHit(coordinate);
    }
    else {
        player2->setBombHitOnPoint(coordinate);
        emit setBombMiss(coordinate);
    }
    qDebug() << "\n";
    player2->DebugPrintField();
}

GameLogicWithComputer::~GameLogicWithComputer() {
    delete player1;
    delete player2;
    delete computer;
}
