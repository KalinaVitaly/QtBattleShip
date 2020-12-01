#ifndef SHIP_H
#define SHIP_H

#include <QObject>

class Ship : public QObject
{
    Q_OBJECT

private:
    QVector<QPair<QPair<int, int>, bool>> ship_coordinates_and_deck_condition;
    int ship_type;
    int deck_count;
    bool is_ship_destroyed;
    bool orientation;
public:
    Ship();

    bool getIsShipDestroyed() const;
    int getShipType() const;
    int getShipDeckCount() const;
    void setShipPosition(const QVector<QPair<int, int>> &position, int _ship_type, bool _orientation);
    bool isShipInjured(const QPair<int, int> &point);
    bool isShipDeath();
    bool isShipPoint(const QPair<int, int> &point);
    bool getOrientation() const;
    QPair<int, int> getShipbegin();
    QVector<QPair<int, int>> getShipCoordinates() const;
public slots:

};
#endif // SHIP_H
