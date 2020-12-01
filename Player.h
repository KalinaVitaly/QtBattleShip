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
    int ship1_count;
    int ship2_count;
    QVector<Ship *> ship1;
    QVector<Ship *> ship2;
    int field[10][10];

    void DebugPrintField() const;
    void findAndDeleteShip(Ship *);
public:
    explicit Player();
    //~Player();

    int getMaxShip1() const;
    bool checkingPointPresenceShip(const QPair<int, int> &point) const;
    bool hasShipOnPoint(const QPair<int, int> & point) const;
    void setBombHitOnPoint(const QPair<int, int> &point);
    Ship* findShipByPosition(const QPair<int, int> & point);
    bool canSetShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates);
    void setShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates, int type, bool orientation);
    QVector<QPair<int, int>> convertPointAndOrientation2Coordinates(const QPair<int, int>& point, int type, bool orientation);
    void deleteShipFromPosition(const QPair<int, int>& point);

signals:

public slots:
};

#endif // PLAYER_H
