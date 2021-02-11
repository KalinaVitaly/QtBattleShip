#include "RadioButtonsAndPushButtons.h"
#include <QDebug>

RadioButtonsAndPushButtons::RadioButtonsAndPushButtons(QWidget * parent) :
    QWidget(parent),
    start(new QPushButton("Start", this)),
    automaticPlacementShips(new QPushButton("Ships automatic placement", this)),
    horizontalRadioButton(new QRadioButton("Horizantal", this)),
    verticalRadioButton(new QRadioButton("Vertival", this)),
    verticalLayout(new QVBoxLayout(this))
{
    this->setFixedSize(480, 880);

    setStyleSheets();

    QFont font("times", 15);
    start->setFlat(true);
    horizontalRadioButton->setChecked(true);

    verticalLayout->addWidget(horizontalRadioButton, Qt::AlignCenter);
    verticalLayout->addWidget(verticalRadioButton, Qt::AlignCenter);
    verticalLayout->addWidget(automaticPlacementShips, Qt::AlignCenter);
    verticalLayout->addWidget(start, Qt::AlignCenter);
}

QPushButton*& RadioButtonsAndPushButtons::getStart() { return start; }
QRadioButton*& RadioButtonsAndPushButtons::getHorizantal() { return horizontalRadioButton; }
QRadioButton*& RadioButtonsAndPushButtons::getVertical() { return verticalRadioButton; }
QPushButton*& RadioButtonsAndPushButtons::getAutoPlacementShips() { return automaticPlacementShips; }

void RadioButtonsAndPushButtons::setStyleSheets() {
    horizontalRadioButton->setStyleSheet("background-color : rgba(135, 206, 235, 100);");
    verticalRadioButton->setStyleSheet("background-color : rgba(135, 206, 235, 100);");

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
    automaticPlacementShips->setStyleSheet("QPushButton {\
                                              color : black;\
                                              background-color : rgba(135, 206, 235, 50);\
                                              font-family: New Century Schoolbook;\
                                              border-width: 2px;\
                                              border-style: outset;\
                                              border-color: beige;\
                                              font-size : 20px;\
                                              border-radius: 10px;\
                                              }\
                                              QPushButton:hover {\
                                              background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                                              stop : 0 #F8F8FF, stop: 1 #E9E9F0);\
                                              }\
                                              QPushButton:pressed {\
                                              background-color : #B2BEB5\
                                              }");
    start->setToolTip("To start the game you need to place all the ships.");
}

RadioButtonsAndPushButtons::~RadioButtonsAndPushButtons()
{

}
