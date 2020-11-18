#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Ship.h"

class Player : public QObject
{
    Q_OBJECT

private:
    int max_ship1;
    int max_ship2;
    int max_ship3;
    int max_ship4;
    int ship1_count;
    int ship2_count;
    int ship3_count;
    int ship4_count;
    Ship *ship1[4];
    Ship *ship2[3];
    Ship *ship3[2];
    Ship *ship4[1];
    int field[10][10];

    Ship** getShipByType(int type);
    int& getByTypeShipCount(int type);
    void setShipPositionInField(int type, const QPair<int, int> &position, bool orientation);
    int getByTypeShipLength(int type);

public:
    explicit Player();
    ~Player();

    void initializationShip(Ship **ship, int ship_type, int deck_count, int count);
    void setShipPosition(int type, const QPair<int, int> &position, bool orientation);
    bool checkHit(const QPair<int, int> &position);
    bool canSetShipInThisPosition(int type, const QPair<int, int> &position, bool orientation);


signals:

public slots:


};

#endif // PLAYER_H
