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

    enum class GAMESTATE {
        FIRST_PLAYER_STEP,
        SECOND_PLAYER_STEP,
        GAME_END
    };

    GAMESTATE state;

    void gameEnd(const QString & information);

public:
    explicit GameLogicWithComputer(Player *player, QObject *parent = nullptr);
    ~GameLogicWithComputer();

    void shootFromComputer();
    QVector<QPair<int, int>> fieldsCoordinatesAroundDestroyededShip(Player *,const QVector<QPair<int, int>> &, bool);

public slots:
    void setShootFromGrid(const QPair<int, int> &);
    void signalProcessing();
    void computerGameStep();

signals:
    void setBombMiss2LabelGrid(const QPair<int, int> &);
    void setBombHit2LabelGrid(const QPair<int, int> &);
    void setBombHitFromComputer(const QPair<int, int> &);
    void setBombMissFromComputer(const QPair<int, int> &);
    void setComputerDestroyedShip(const QVector<QPair<int, int>> &);
    void setAroundDestroyededShipInactiveFields(const QVector<QPair<int, int>> &);
    void setAroundDestroyededPlayerShipFields(const QVector<QPair<int, int>> &);
    void playerClickedField(QPushButton *);
    void beginComputerGameStep();

    void signalEndGame(const QString &);

};

#endif // GAMELOGIC_H
