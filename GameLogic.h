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
    ~GameLogicWithComputer() override;

    void shootFromComputer();
    QVector<QPair<int, int>> fieldsCoordinatesAroundDestroyededShip(Player *,const QVector<QPair<int, int>> &, bool);

public slots:
    void slotSetShootFromGrid(const QPair<int, int> &);
    void slotProcessing();
    void slotComputerGameStep();

signals:
    void signalSetBombMiss2LabelGrid(const QPair<int, int> &);
    void signalSetBombHit2LabelGrid(const QPair<int, int> &);
    void signalSetBombHitFromComputer(const QPair<int, int> &);
    void signalSetBombMissFromComputer(const QPair<int, int> &);
    void signalSetComputerDestroyedShip(const QVector<QPair<int, int>> &);
    void signalSetAroundDestroyededShipInactiveFields(const QVector<QPair<int, int>> &);
    void signalSetAroundDestroyededPlayerShipFields(const QVector<QPair<int, int>> &);
    void signalPlayerClickedField(Button *);
    void signalBeginComputerGameStep();

    void signalEndGame(const QString &);

};

#endif // GAMELOGIC_H
