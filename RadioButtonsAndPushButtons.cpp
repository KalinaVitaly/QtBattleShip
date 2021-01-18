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
    start->setStyleSheet("background: rgba(255,255,255,100);\
                          border-style: outset;\
                          border-width: 2px;\
                          border-color: beige;");
    start->setFlat(true);
    horizontal->setChecked(true);
    horizontal->setStyleSheet("background-color : rgba(135, 206, 235, 100);");
    vertical->setStyleSheet("background-color : rgba(135, 206, 235, 100);");
    automatic_placement_ships->setStyleSheet("background-color : rgba(135, 206, 235, 50);");
    start->setToolTip("To start the game you need to place all the ships.");

    vertical_layout->addWidget(horizontal, Qt::AlignCenter);
    vertical_layout->addWidget(vertical, Qt::AlignCenter);
    vertical_layout->addWidget(automatic_placement_ships, Qt::AlignCenter);
    vertical_layout->addWidget(start, Qt::AlignCenter);
}

QPushButton*& RadioButtonsAndPushButtons::getStart() { return start; }
QRadioButton*& RadioButtonsAndPushButtons::getHorizantal() { return horizontal; }
QRadioButton*& RadioButtonsAndPushButtons::getVertical() { return vertical; }
QPushButton*& RadioButtonsAndPushButtons::getAutoPlacementShips() { return automatic_placement_ships; }

RadioButtonsAndPushButtons::~RadioButtonsAndPushButtons() {
    delete vertical_layout;
    delete start;
    delete horizontal;
    delete vertical;
    delete automatic_placement_ships;
}
