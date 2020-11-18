#include "ShipsWidget.h"

ShipsWidget::ShipsWidget(QWidget *parent) : QWidget(parent)
{
    vertical_layout = new QVBoxLayout;
    setButtonAndLabel(horiz_layout1, ship1, dig1, pix_ship1, pix_one);
    setButtonAndLabel(horiz_layout2, ship2, dig2, pix_ship2, pix_two);
    setButtonAndLabel(horiz_layout3, ship3, dig3, pix_ship3, pix_three);
    setButtonAndLabel(horiz_layout4, ship4, dig4, pix_ship4, pix_four);
    this->setLayout(vertical_layout);
    this->setFixedSize(300, 880);
}

int ShipsWidget::getClickedShipType() const { return choose_ship_type; }

void ShipsWidget::setButtonAndLabel(QHBoxLayout *&layout, QPushButton *&button, QLabel *&label, QPixmap *&pix, QPixmap *&pix2)
{
    static int i = 1;
    layout = new QHBoxLayout;
    //QImage("/home/vitaly/QtProject/BattleShips/images/ships/" + QString::number(i) + ".png").scaled(220, 120).save("/home/vitaly/QtProject/BattleShips/images/ships/" + QString::number(i) + ".png");
    //QImage("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png").scaled(120, 80).save("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
    pix = new QPixmap("/home/vitaly/QtProject/BattleShips/images/ships/" + QString::number(i) + ".png");
    pix2 = new QPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
    button = new QPushButton(*pix, "", this);
    button->setIconSize(QSize(120, 120));
    button->setFlat(true);
    label = new QLabel;
    label->setPixmap(*pix2);
    label->setFixedSize(120, 80);
    layout->addWidget(button, 0, Qt::AlignLeft);
    layout->addWidget(label, 0, Qt::AlignRight);
    vertical_layout->addLayout(layout);
    ++i;

    QObject::connect(button, SIGNAL(clicked()),
                     this, SLOT(shipClicked()));
}

void ShipsWidget::changeDigit()
{

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

    QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    //this->setCursor(Qt::ClosedHandCursor);
}
