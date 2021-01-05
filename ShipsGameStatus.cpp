#include "ShipsGameStatus.h"

ShipsGameStatus::ShipsGameStatus(QWidget * parent) :
    QWidget(parent),
    ships_pix(4),
    destroyed_ships_pix(4) { }

void ShipsGameStatus::setShipsPixMap(const QString & path, QVector<QPixmap *> &pix) {
    for (int i = 0; i < 4; ++i) {
        pix[i] = new QPixmap(path + QString::number(i + 1) + ".jpg");
    }
}
