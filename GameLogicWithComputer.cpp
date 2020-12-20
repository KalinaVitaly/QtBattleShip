#include "GameLogicWithComputer.h"
#include <QDebug>

GameLogicWithComputer::GameLogicWithComputer(Player *player, QObject *parent) : QObject(parent),
                                        player1(player),
                                        turn(rand() % 2)
{
    computer = new ComputerPlayer;
    player2 = new Player;

    AutomaticShipsPlacement::setRandomPositionShips(player2);

    //Debug output
//    QString output_str = "";
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            output_str += QString::number(player2->getField()[i][j]);
//        }
//        qDebug() << output_str;
//        output_str = "";
//    }
}

void GameLogicWithComputer::gameCycle() {

    while (true) {
//        pla
    }
}

void GameLogicWithComputer::shootFromComputer() {
    qDebug() << "Start";
    QPair<int, int> coordinate = computer->Shooting();
    qDebug() << "Shooting";
    if (player1->hasShipOnPoint(coordinate)) {
        qDebug() << "Start1";
        player1->setBombHitOnPoint(coordinate);
        qDebug() << "Start2";
        emit setComputerBombHit(coordinate);
        qDebug() << "Start3";
    }
    else {
        qDebug() << "Start4";
        player1->setBombHitOnPoint(coordinate);
        qDebug() << "Start5";
        emit setComputerBombMiss(coordinate);
        qDebug() << "Start6";
    }
}

void GameLogicWithComputer::setShootFromGrid(const QPair<int, int> & coordinate) {
    if (player2->hasShipOnPoint(coordinate)) {
        player2->setBombHitOnPoint(coordinate);
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
