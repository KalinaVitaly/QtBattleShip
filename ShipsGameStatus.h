#ifndef SHIPSGAMESTATUS_H
#define SHIPSGAMESTATUS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class ShipsGameStatus : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *players_ships;
    QHBoxLayout *player_ships;
    QHBoxLayout *enemy_ships;
    QVector<QPixmap *> ships_pix;
    QVector<QPixmap *> destroyed_ships_pix;
    QVector<QLabel *> players_ships_labels;
    QVector<QLabel *> enemy_ships_labels;

    void setShipsPixMap(const QString & path, QVector<QPixmap *> &pix);

public:
    ShipsGameStatus(QWidget * parent = nullptr);
};

#endif // SHIPSGAMESTATUS_H
