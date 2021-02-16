#include "ShipsWidget.h"
#include <bits/stdc++.h>
#include <QDebug>

ShipsWidget::ShipsWidget(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    digitsLabel(new QMap<int, QLabel *>),
    shipsButton(new QMap<int, QPushButton *>),
    digitPixmap(new QMap<int, QPixmap *>),
    shipPixmap(new QMap<int, QPixmap *>)
{
    for (int i = 1; i < 5; ++i) {
        haveShips.insert(i, 5 - i);
    }

    setButtonAndLabel(horizLayout1, (*shipsButton)[1], (*digitsLabel)[1], (*shipPixmap)[1], (*digitPixmap)[1], 1);
    setButtonAndLabel(horizLayout2, (*shipsButton)[2], (*digitsLabel)[2], (*shipPixmap)[2], (*digitPixmap)[2], 2);
    setButtonAndLabel(horizLayout3, (*shipsButton)[3], (*digitsLabel)[3], (*shipPixmap)[3], (*digitPixmap)[3], 3);
    setButtonAndLabel(horizLayout4, (*shipsButton)[4], (*digitsLabel)[4], (*shipPixmap)[4], (*digitPixmap)[4], 4);

    setLayout(mainLayout);
    setFixedSize(300, 880);
}

void ShipsWidget::setChooseShipType(int type) { chooseShipType = type; }

int ShipsWidget::getClickedShipType() const { return chooseShipType; }

void ShipsWidget::setChooseShip(int type) { chooseShipType = type; }

void ShipsWidget::updateDigits() {
    for (int i = 1; i <= 4; ++i) {
        (*digitsLabel)[chooseShipType]->setText(QString::number(haveShips[chooseShipType]));
        //(*digitsLabel)[i]->setPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(haveShips[i]) + ".png");
    }
}

void ShipsWidget::slotSetNulls() {
    for (int i = 1; i < 5; ++i) {
        haveShips[i] = 0;
    }

    updateDigits();
}

void ShipsWidget::slotSetMax() {
    for (int i = 1; i < 5; ++i) {
        haveShips[i] = 5 - i;
    }

    updateDigits();
}

void ShipsWidget::setButtonAndLabel(QHBoxLayout *&layout, QPushButton *&button, QLabel *&label, QPixmap *&pix, QPixmap *&pix2, int i)
{
    QFont font("New Century Schoolbook");
    font.setPointSize(30);
    layout = new QHBoxLayout();
    pix = new QPixmap(":/images/ships/" + QString::number(i) + ".png");
    button = new QPushButton(*pix, "", this);
    label = new QLabel(this);

    button->setIconSize(QSize(120, 120));
    button->setFlat(true);
//    label->setPixmap(*pix2);
    label->setText(QString::number(5 - i));
    label->setFont(font);
    label->setFixedSize(120, 80);
    label->setAttribute(Qt::WA_TranslucentBackground);
    button->setAttribute(Qt::WA_TranslucentBackground);

    layout->addWidget(button, 0, Qt::AlignLeft);
    layout->addWidget(label, 0, Qt::AlignRight);
    mainLayout->addLayout(layout);

    connect(button, SIGNAL(clicked()),
        this, SLOT(slotShipClicked()));
}

void ShipsWidget::changeDigitPixMap() {
    --haveShips[chooseShipType];
    (*digitsLabel)[chooseShipType]->setText(QString::number(haveShips[chooseShipType]));

    checkingBeforeGameStarting();
}

void ShipsWidget::returnChangedDigitPixMap() {
    ++haveShips[chooseShipType];
    (*digitsLabel)[chooseShipType]->setText(QString::number(haveShips[chooseShipType]));

    checkingBeforeGameStarting();
}

void ShipsWidget::slotShipClicked() {
    if ((QPushButton*)sender() == (*shipsButton)[1]) {
        chooseShipType = 1;
    } else if ((QPushButton*)sender() == (*shipsButton)[2]) {
        chooseShipType = 2;
    } else if ((QPushButton*)sender() == (*shipsButton)[3]) {
        chooseShipType = 3;
    } else if ((QPushButton*)sender() == (*shipsButton)[4]) {
        chooseShipType = 4;
    }

    if((chooseShipType == 1 && haveShips[1] > 0) ||
            (chooseShipType == 2 && haveShips[2] > 0) ||
            (chooseShipType == 3 && haveShips[3] > 0) ||
            (chooseShipType == 4 && haveShips[4] > 0)) {
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }
}

void ShipsWidget::checkingBeforeGameStarting() {
    if (haveShips[1] | haveShips[2] | haveShips[3] | haveShips[4]) {
        emit signalHideStartGame();
    } else {
        emit signalShowStartGame();
    }
}

ShipsWidget::~ShipsWidget() {
    for (int i = 1; i < 5; ++i) {
        delete (*digitPixmap)[i];
        delete (*shipPixmap)[i];
        delete (*digitsLabel)[i];
    }
}
