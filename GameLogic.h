#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <random>
#include <QPushButton>
#include "AutomaticShipsPlacement.h"
#include "ComputerPlayer.h"
#include "Player.h"

class GameLogic : public QObject
{
    Q_OBJECT
private:
    Player *player1;
    Player *player2;

    bool turn;


public:
    GameLogic(Player *player, QObject *parent = nullptr);

    void gameCycle();

public slots:
    void setShootFromGrid(const QPair<int, int> &);
signals:
    void setBombMiss(const QPair<int, int> &);
    void setBombHit(const QPair<int, int> &);
};

#endif // GAMELOGIC_H
