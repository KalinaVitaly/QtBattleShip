#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Ship.h"

class Player
{
    //Q_OBJECT

private:
    static const int max_ship1;
    static const int max_ship2;
    static const int max_ship3;
    static const int max_ship4;
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
    void deleteShipFromField(const QPair<int, int> &position, bool orientation, int deck_count);

public:
    explicit Player();
    ~Player();

    int getMaxShip1() const;
    int getMaxShip2() const;
    int getMaxShip3() const;
    int getMaxShip4() const;
    void initializationShip(Ship **ship, int ship_type, int deck_count, int count);
    void setShipPosition(int type, const QPair<int, int> &position, bool orientation);
    bool checkHit(const QPair<int, int> &position);
    bool canSetShipInThisPosition(int type, const QPair<int, int> &position, bool orientation);
    void deleteShipFromPosition();
    Ship*& findShipOnField(const QPair<int, int> &point);
    bool hasShipOnPosition(const QPair<int, int> &point);
    void setNewShipPosition(Ship *ship, const QPair<int, int> &position, bool orientation);
signals:

public slots:
};

#endif // PLAYER_H
