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
public:
    Ship(int ship_type, int deck_count);

    int getShipType() const;
    int getShipDeckCount() const;
    void setShipPosition(const QPair<int, int> &point, bool orientation);
    bool isShipInjured(const QPair<int, int> &point);
    bool isShipDeath();
public slots:

};

#endif // SHIP_H
