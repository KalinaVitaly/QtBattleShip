#include "GridWidget.h"
#include <QDebug>

GridWidget::GridWidget(QWidget *parent) :
    QWidget(parent),
    field_count(100)
{
    this->setFixedSize(880, 880);
    grid = new QGridLayout(this);
    field = new QPixmap("/home/vitaly/QtProject/BattleShips/images/field/field.jpg");

    setSymbols();
    setDigits();
    setFields();
    this->setLayout(grid);
}

QPushButton** GridWidget::getField() { return  buttons_sea_fieald; }
size_t GridWidget::getFieldCount() { return field_count; }


void GridWidget::setShipPositionInGrid(const QPair<int, int> &pos, bool orientation, int length)
{
    //qDebug() << "setShipPositionInGrid:";
    if (orientation) {
        for(int i = 0; i < length; ++i) {
             buttons_sea_fieald[pos.first + 10 * pos.second + i]->setIcon(QPixmap());
             buttons_sea_fieald[pos.first + 10 * pos.second + i]->setStyleSheet("background-color: grey;\
                                                                           border-style: outset;\
                                                                           border-width: 2px;\
                                                                           border-color: beige;");
        }
    }
    else {
        for(int i = 0; i < length; ++i) {
             //qDebug() << pos.first << " " << pos.second << " " << pos.first + 10 * pos.second + i * 10;
             buttons_sea_fieald[pos.first + 10 * pos.second + i * 10]->setIcon(QPixmap());
             buttons_sea_fieald[pos.first + 10 * pos.second + i * 10]->setStyleSheet("background-color: grey;\
                                                                           border-style: outset;\
                                                                           border-width: 2px;\
                                                                           border-color: beige;");
        }
    }
    //qDebug() << "End";
}

void GridWidget::setFieldPixOnShipPositionInGrid(const QVector<QPair<int, int>> &pos, bool orientation)
{
    //qDebug() << "setFieldPixOnShipPositionInGrid";
    if (orientation) {
        for(int i = 0; i < pos.size(); ++i) {
             buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setIcon(*field);
             buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setIconSize(QSize(80, 80));
             buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setFlat(false);
        }
    }
    else {
        for(int i = 0; i < pos.size(); ++i) {
             //qDebug() << pos[i].first << " " << pos[i].second << " " << pos[i].first + 10 * pos[i].second + i * 10;
             buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setIcon(*field);
             buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setIconSize(QSize(80, 80));
             buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setFlat(false);
        }
    }
    //qDebug() << "End";
}

size_t GridWidget::findFieldNumber(QPushButton *button)
{
    for(size_t i = 0; i < field_count; ++i)
        if(buttons_sea_fieald[i] == button)
            return i;
    return -1;
}

void GridWidget::setFields()
{
    for (size_t i = 0; i < field_count; ++i)
    {
        buttons_sea_fieald[i] = new QPushButton(*field, "", this);
        buttons_sea_fieald[i]->setIconSize(QSize(80, 80));
        buttons_sea_fieald[i]->setFlat(false);
        buttons_sea_fieald[i]->setFixedSize(QSize(80, 80));
        grid->addWidget(buttons_sea_fieald[i], 1 + i / 10, 1 + i % 10, Qt::AlignCenter);
    }
}

void GridWidget::setGameFields()
{
    for (size_t i = 0; i < field_count; ++i)
    {
        buttons_sea_fieald[i] = new QPushButton(*field, "", this);
        buttons_sea_fieald[i]->setIconSize(QSize(80, 80));
        buttons_sea_fieald[i]->setFlat(false);
        buttons_sea_fieald[i]->setFixedSize(QSize(80, 80));
        grid->addWidget(buttons_sea_fieald[i], 1 + i / 10, 1 + i % 10, Qt::AlignCenter);
    }
}

void GridWidget::setSymbols()
{
    for (int i = 1; i <= 10; ++i)
    {
        //QImage("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".jpg").scaled(80, 80).save("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".jpg");
        QPixmap *pix = new QPixmap("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".jpg");
        symbols.push_back(pix);
        QLabel *label = new QLabel;
        label->setPixmap(*(symbols[i - 1]));
        label->setFixedSize(70, 70);
        grid->addWidget(label, 0, i, Qt::AlignCenter);
    }
}

void GridWidget::setDigits()
{
    for (int i = 1; i <= 10; ++i)
    {
        QImage("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png").scaled(80, 80).save("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
        QPixmap *pix = new QPixmap("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
        QLabel *label = new QLabel;
        digit.push_back(pix);
        label->setPixmap(*(digit[i - 1]));
        label->setFixedSize(80, 80);
        grid->addWidget(label, i, 0, Qt::AlignCenter);
    }
}
