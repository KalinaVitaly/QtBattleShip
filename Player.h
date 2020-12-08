#ifndef PLAYER_H
#define PLAYER_H

#include <QMap>
#include "Ship.h"
#include <array>

class Player : public QObject
{
    Q_OBJECT

private:
    static const int max_ship1;
    static const int max_ship2;
    static const int max_ship3;
    static const int max_ship4;
    QMap<int, QVector<Ship *>> ships;
    QMap<int, int> ships_count;
    std::array<std::array<int, 10>, 10> field;

    //void DebugPrintField() const;
    void findAndDeleteShip(Ship *);
    bool checkingPossiblePutInFrontOfTheVerticalShip(const QPair<int, int> &center) const;
    bool checkingPossiblePutInBackOfTheVerticalShip(const QPair<int, int> &center) const;
    bool checkingPossiblePutInFrontOfTheHorizantalShip(const QPair<int, int> &center) const;
    bool checkingPossiblePutInBackOfTheHorizantalShip(const QPair<int, int> &center) const;
public:
    explicit Player();
    ~Player();

    std::array<std::array<int, 10>, 10> getField();
    int getShipCount(int type) const;
    bool checkingPointPresenceShip(const QPair<int, int> &point) const;
    bool hasShipOnPoint(const QPair<int, int> & point) const;
    void setBombHitOnPoint(const QPair<int, int> &point);
    Ship* findShipByPosition(const QPair<int, int> & point);
    bool canSetShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates, bool orientation);
    void setShipOnPosition(const QVector<QPair<int, int>> & ship_coordinates, int type, bool orientation);
    QVector<QPair<int, int>> convertPointAndOrientation2Coordinates(const QPair<int, int>& point, int type, bool orientation);
    void deleteShipFromPosition(const QPair<int, int>& point);
    void DebugPrintField();
    void deleteAllShips();
signals:
    void deleteShipFromFields(const QVector<QPair<int, int>> & pos, bool orientation);
public slots:
};

#endif // PLAYER_H
