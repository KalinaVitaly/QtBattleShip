#ifndef SHIP_H
#define SHIP_H

#include <QObject>

class Ship : public QObject
{
    Q_OBJECT

private:
    QVector<QPair<QPair<int, int>, bool>> ship_coordinates_and_deck_condition;
    int typeOfShip;
    int deckCount;
    bool isShipDestroyeded;
    bool orientationOfShip;
public:
    Ship();

    bool getIsShipDestroyeded() const;
    int getTypeOfShip() const;
    int getShipDeckCount() const;
    void setShipPosition(const QVector<QPair<int, int>> &position, int _ship_type, bool _orientation);
    bool isShipInjured(const QPair<int, int> &point);
    bool isShipDeath();
    bool isShipPoint(const QPair<int, int> &point);
    bool getOrientationOfShip() const;
    QPair<int, int> getShipBegin();
    QVector<QPair<int, int>> getShipCoordinates();
};
#endif // SHIP_H
