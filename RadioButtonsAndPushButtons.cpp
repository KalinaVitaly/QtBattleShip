#include "RadioButtonsAndPushButtons.h"
#include <QDebug>

RadioButtonsAndPushButtons::RadioButtonsAndPushButtons(QWidget * parent) : QWidget(parent)
{
    this->setFixedSize(480, 880);
    vertical_layout = new QVBoxLayout(this);
    start = new QPushButton("Start");
    horizontal = new QRadioButton("Horizantal");
    vertical = new QRadioButton("Vertival");
    automatic_placement_ships = new QPushButton("Ships automatic placement");

    QFont font("times", 15);
    start->setFont(font);
    start->setStyleSheet("QAbstractButton {\
                        background: rgba(255,255,255,100);\
                        border-style: outset;\
                        border-width: 2px;\
                        border-color: beige;\
                 }");
    start->setFlat(true);
    horizontal->setFont(font);
    vertical->setFont(font);
    horizontal->setChecked(true);

    qDebug() << start->geometry();

    vertical_layout->addWidget(horizontal, Qt::AlignCenter);
    vertical_layout->addWidget(vertical, Qt::AlignCenter);
    vertical_layout->addWidget(automatic_placement_ships, Qt::AlignCenter);
    vertical_layout->addWidget(start, Qt::AlignCenter);
}

QPushButton*& RadioButtonsAndPushButtons::getStart() { return start; }
QRadioButton*& RadioButtonsAndPushButtons::getHorizantal() { return horizontal; }
QRadioButton*& RadioButtonsAndPushButtons::getVertical() { return vertical; }
QPushButton*& RadioButtonsAndPushButtons::getAutoPlacementShips() { return automatic_placement_ships; }
