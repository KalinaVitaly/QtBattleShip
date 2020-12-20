#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <random>
#include <QPushButton>
#include "AutomaticShipsPlacement.h"
#include "ComputerPlayer.h"
#include "Player.h"

class GameLogicWithComputer : public QObject
{
    Q_OBJECT
private:
    Player *player1;
    Player *player2;
    ComputerPlayer *computer;
    bool turn;

public:
    GameLogicWithComputer(Player *player, QObject *parent = nullptr);
    ~GameLogicWithComputer();
    void gameCycle();
    void shootFromComputer();

public slots:
    void setShootFromGrid(const QPair<int, int> &);
signals:
    void setBombMiss(const QPair<int, int> &);
    void setBombHit(const QPair<int, int> &);
    void setComputerBombHit(const QPair<int, int> &);
    void setComputerBombMiss(const QPair<int, int> &);
};

#endif // GAMELOGIC_H
