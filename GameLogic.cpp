#include "GameLogic.h"
#include <QDebug>

GameLogic::GameLogic(Player *player, QObject *parent) : QObject(parent),
                                        player1(player),
                                        turn(rand() % 2)
{
    player2 = new Player;
    AutomaticShipsPlacement::setRandomPositionShips(player2);
    QString output_str = "";
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            output_str += QString::number(player2->getField()[i][j]);
        }
        qDebug() << output_str;
        output_str = "";
    }
}

void GameLogic::gameCycle() {

    while (true) {
//        pla
    }
}

void GameLogic::setShootFromGrid(const QPair<int, int> & coordinate) {
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
