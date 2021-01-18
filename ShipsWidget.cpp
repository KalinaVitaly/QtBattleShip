#include "ShipsWidget.h"
#include <QDebug>

ShipsWidget::ShipsWidget(QWidget *parent) :
    QWidget(parent) {
    have_ships.insert(1, 4);
    have_ships.insert(2, 3);
    have_ships.insert(3, 2);
    have_ships.insert(4, 1);
    vertical_layout = new QVBoxLayout;
    //old -----------------------------------------------------------------
    setButtonAndLabel(horiz_layout1, button_ships[1], label_digits[1], pix_ship[1], pix_digit[1], 1);
    setButtonAndLabel(horiz_layout2, button_ships[2], label_digits[2], pix_ship[2], pix_digit[2], 2);
    setButtonAndLabel(horiz_layout3, button_ships[3], label_digits[3], pix_ship[3], pix_digit[3], 3);
    setButtonAndLabel(horiz_layout4, button_ships[4], label_digits[4], pix_ship[4], pix_digit[4], 4);
    //old -----------------------------------------------------------------
    this->setLayout(vertical_layout);
    this->setFixedSize(300, 880);
}

void ShipsWidget::setChooseShipType(int type) { choose_ship_type = type; }

int ShipsWidget::getClickedShipType() const { return choose_ship_type; }

void ShipsWidget::setChooseShip(int type) { choose_ship_type = type; }

void ShipsWidget::updateDigits() {
    //new ------------------------------------------------------------------------------------------------------------------------
    for (int i = 1; i <= 4; ++i) {
        label_digits[i]->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(have_ships[i]) + ".png");
    }
    //new ------------------------------------------------------------------------------------------------------------------------
}

void ShipsWidget::setNulls() {
   //new -------------------------------------------------
   have_ships[1] = 0;
   have_ships[2] = 0;
   have_ships[3] = 0;
   have_ships[4] = 0;
   //new -------------------------------------------------
   updateDigits();
}

void ShipsWidget::setMax() {
   have_ships[1] = 4;
   have_ships[2] = 3;
   have_ships[3] = 2;
   have_ships[4] = 1;

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
    label->setAttribute(Qt::WA_TranslucentBackground);
    button->setAttribute(Qt::WA_TranslucentBackground);
    layout->addWidget(button, 0, Qt::AlignLeft);
    layout->addWidget(label, 0, Qt::AlignRight);
    vertical_layout->addLayout(layout);

    QObject::connect(button, SIGNAL(clicked()),
                     this, SLOT(shipClicked()));
}

void ShipsWidget::changeDigitPixMap()
{
    //new ---------------------------------------------------------------------------------------------
    --have_ships[choose_ship_type];
    label_digits[choose_ship_type]->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" +
                                              QString::number(have_ships[choose_ship_type]) + ".png");
    //new ---------------------------------------------------------------------------------------------

    checkingBeforeGameStarting();
}

void ShipsWidget::returnChangedDigitPixMap()
{
    //new --------------------------------------------------------------------------------------------
    ++have_ships[choose_ship_type];
    label_digits[choose_ship_type]->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" +
                                              QString::number(have_ships[choose_ship_type]) + ".png");
    //new --------------------------------------------------------------------------------------------

    checkingBeforeGameStarting();
}

void ShipsWidget::shipClicked()
{
    if ((QPushButton*)sender() == button_ships[1])
        choose_ship_type = 1;
    else if ((QPushButton*)sender() == button_ships[2])
        choose_ship_type = 2;
    else if ((QPushButton*)sender() == button_ships[3])
        choose_ship_type = 3;
    else if ((QPushButton*)sender() == button_ships[4])
        choose_ship_type = 4;

    //qDebug() << "Choose ship type: " << choose_ship_type;
    if((choose_ship_type == 1 && have_ships[1] > 0) ||
       (choose_ship_type == 2 && have_ships[2] > 0) ||
       (choose_ship_type == 3 && have_ships[3] > 0) ||
       (choose_ship_type == 4 && have_ships[4] > 0)) {
        //qDebug() << "Set cursor: ClosedHandCursor";
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }
}

void ShipsWidget::checkingBeforeGameStarting()
{
    //new -----------------------------------------------------------------
    if (have_ships[1] | have_ships[2] | have_ships[3] | have_ships[4]) {
        emit hideStartGame();
    }
    else {
        emit showStartGame();
    }
    //new -----------------------------------------------------------------
}
