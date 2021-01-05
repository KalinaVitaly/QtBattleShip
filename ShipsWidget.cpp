#include "ShipsWidget.h"
#include <QDebug>

ShipsWidget::ShipsWidget(QWidget *parent) :
    QWidget(parent),
    have_ship1(4),
    have_ship2(3),
    have_ship3(2),
    have_ship4(1)
{
    vertical_layout = new QVBoxLayout;
    setButtonAndLabel(horiz_layout1, ship1, dig1, pix_ship1, pix_one, 1);
    setButtonAndLabel(horiz_layout2, ship2, dig2, pix_ship2, pix_two, 2);
    setButtonAndLabel(horiz_layout3, ship3, dig3, pix_ship3, pix_three, 3);
    setButtonAndLabel(horiz_layout4, ship4, dig4, pix_ship4, pix_four, 4);
    this->setLayout(vertical_layout);
    this->setFixedSize(300, 880);
}

void ShipsWidget::setChooseShipType(int type) { choose_ship_type = type; }

int ShipsWidget::getClickedShipType() const { return choose_ship_type; }

void ShipsWidget::setChooseShip(int type) { choose_ship_type = type; }

void ShipsWidget::updateDigits() {
    dig1->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship1) + ".png");
    dig2->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship2) + ".png");
    dig3->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship3) + ".png");
    dig4->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship4) + ".png");
}

void ShipsWidget::setNulls() {
     have_ship1 = have_ship2 = have_ship3 = have_ship4 = 0;
     updateDigits();
}

void ShipsWidget::setMax() {
   have_ship1 = 4;
   have_ship2 = 3;
   have_ship3 = 2;
   have_ship4 = 1;
   updateDigits();
}

void ShipsWidget::setButtonAndLabel(QHBoxLayout *&layout, QPushButton *&button, QLabel *&label, QPixmap *&pix, QPixmap *&pix2, int i)
{
    layout = new QHBoxLayout;
    //QImage("/home/vitaly/QtProject/BattleShips/images/ships/" + QString::number(i) + ".png").scaled(220, 120).save("/home/vitaly/QtProject/BattleShips/images/ships/" + QString::number(i) + ".png");
    //QImage("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png").scaled(120, 80).save("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
    pix = new QPixmap("/home/vitaly/QtProject/BattleShips/images/ships/" + QString::number(i) + ".png");
    pix2 = new QPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(5 - i) + ".png");
    button = new QPushButton(*pix, "", this);
    button->setIconSize(QSize(120, 120));
    button->setFlat(true);
    label = new QLabel;
    label->setPixmap(*pix2);
    label->setFixedSize(120, 80);
    layout->addWidget(button, 0, Qt::AlignLeft);
    layout->addWidget(label, 0, Qt::AlignRight);
    vertical_layout->addLayout(layout);

    QObject::connect(button, SIGNAL(clicked()),
                     this, SLOT(shipClicked()));
}

void ShipsWidget::changeDigitPixMap()
{
    if (choose_ship_type == 1) {
        --have_ship1;
        dig1->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship1) + ".png");
    }
    else if (choose_ship_type == 2) {
        --have_ship2;
        dig2->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship2) + ".png");
    }
    else if (choose_ship_type == 3) {
        --have_ship3;
        dig3->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship3) + ".png");
    }
    else if (choose_ship_type == 4) {
        --have_ship4;
        dig4->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship4) + ".png");
    }
    checkingBeforeGameStarting();
}

void ShipsWidget::returnChangedDigitPixMap()
{
    if (choose_ship_type == 1) {
        ++have_ship1;
        dig1->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship1) + ".png");
    }
    else if (choose_ship_type == 2) {
        ++have_ship2;
        dig2->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship2) + ".png");
    }
    else if (choose_ship_type == 3) {
        ++have_ship3;
        dig3->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship3) + ".png");
    }
    else if (choose_ship_type == 4) {
        ++have_ship4;
        dig4->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ship4) + ".png");
    }
    checkingBeforeGameStarting();
}

void ShipsWidget::shipClicked()
{
    if ((QPushButton*)sender() == ship1)
        choose_ship_type = 1;
    else if ((QPushButton*)sender() == ship2)
        choose_ship_type = 2;
    else if ((QPushButton*)sender() == ship3)
        choose_ship_type = 3;
    else if ((QPushButton*)sender() == ship4)
        choose_ship_type = 4;

    if((choose_ship_type == 1 && have_ship1 > 0) ||
            (choose_ship_type == 2 && have_ship2 > 0) ||
            (choose_ship_type == 3 && have_ship3 > 0) ||
            (choose_ship_type == 4 && have_ship4 > 0))
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
}

void ShipsWidget::checkingBeforeGameStarting()
{
    if (have_ship1 | have_ship2 | have_ship3 | have_ship4) {
        emit hideStartGame();
    }
    else {
        emit showStartGame();
    }
}
