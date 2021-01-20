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
    start->setFlat(true);
    horizontal->setChecked(true);
    horizontal->setStyleSheet("background-color : rgba(135, 206, 235, 100);");
    vertical->setStyleSheet("background-color : rgba(135, 206, 235, 100);");

    start->setStyleSheet("QPushButton {\
                         color : black;\
                         background-color : rgba(135, 206, 235, 50);\
                         font-family: New Century Schoolbook;\
                         border-width: 2px;\
                         border-style: outset;\
                         border-color: beige;\
                         font-size : 20px;\
                         border-radius: 10px;\
                         }");
    automatic_placement_ships->setStyleSheet("QPushButton {\
                                              color : black;\
                                              background-color : rgba(135, 206, 235, 50);\
                                              font-family: New Century Schoolbook;\
                                              border-width: 2px;\
                                              border-style: outset;\
                                              border-color: beige;\
                                              font-size : 20px;\
                                              border-radius: 10px;\
                                              }\
                                              QPushButton:pressed {\
                                              background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                                              stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                                              }");
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
