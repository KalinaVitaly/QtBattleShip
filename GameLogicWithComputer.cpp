#include "GameLogicWithComputer.h"
#include <QDebug>

GameLogicWithComputer::GameLogicWithComputer(Player *player, QObject *parent) :
                                        QObject(parent),
                                        player1(player)
{
    computer = new ComputerPlayer;
    player2 = new Player;

    state = rand() % 2 ?
                GAMESTATE::FIRST_PLAYER_STEP :
                GAMESTATE::SECOND_PLAYER_STEP;

    AutomaticShipsPlacement::setRandomPositionShips(player2);

    QObject::connect(this, SIGNAL(beginComputerGameStep()),
                     this, SLOT(computerGameStep()));
}

void GameLogicWithComputer::computerGameStep() {
    if (state == GAMESTATE::SECOND_PLAYER_STEP) {
        state = GAMESTATE::FIRST_PLAYER_STEP;
        shootFromComputer();

        if (player1->isShipsDestroyeded()) {
            state = GAMESTATE::GAME_END;
            result_menu = new ResultMenu("LOSE!");
            result_menu->show();
            qDebug() << "Second player win";
        }
    }
}

void GameLogicWithComputer::signalProcessing() {
    if (state == GAMESTATE::FIRST_PLAYER_STEP) {
        QPushButton *field = (QPushButton*)sender();
        state = GAMESTATE::SECOND_PLAYER_STEP;
        emit playerClickedField(field);
        emit beginComputerGameStep();

        if (player2->isShipsDestroyeded()) {
            state = GAMESTATE::GAME_END;
            result_menu = new ResultMenu("WIN!");
            result_menu->show();
            qDebug() << "First player win";
        }
    }
}

bool GameLogicWithComputer::isGameEnd() const {
    return player1->isShipsDestroyeded() && player2->isShipsDestroyeded();
}



QVector<QPair<int, int>> GameLogicWithComputer::fieldsCoordinatesAroundDestroyededShip(
        Player *player, const QVector<QPair<int, int>> & ship_coordinates, bool orientation) {
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

    if (player1->hasShipOnPoint(coordinate)) {
        player1->setBombHitOnPoint(coordinate);

        if (player1->isShipDestroyed(coordinate)) {
            QVector<QPair<int, int>> fields_around_ship = fieldsCoordinatesAroundDestroyededShip(player1,
                player1->getShipCoordinate(coordinate), player1->getShipOrientation(coordinate));
            player1->DebugPrintField();
            emit setAroundDestroyededPlayerShipFields(fields_around_ship);
        }
        emit setBombHitFromComputer(coordinate);
    }
    else {
        player1->setBombHitOnPoint(coordinate);
        emit setBombMissFromComputer(coordinate);
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
        emit setBombHit2LabelGrid(coordinate);
    }
    else {
        player2->setBombHitOnPoint(coordinate);
        emit setBombMiss2LabelGrid(coordinate);
    }
    qDebug() << "\n";
    player2->DebugPrintField();
}

GameLogicWithComputer::~GameLogicWithComputer() {
    delete player1;
    delete player2;
    delete computer;
}
