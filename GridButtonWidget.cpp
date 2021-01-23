#include "GridButtonWidget.h"
#include <QDebug>

GridWidget::GridWidget(QSize field_size, QWidget *parent) :
    QWidget(parent),
    grid(new QGridLayout(this)),
    field(new QPixmap("/home/vitaly/QtProject/BattleShips/images/field/field.jpg")),
    symbol_label(10),
    digit_label(10),
    field_count(100),
    size(field_size)
{
    this->setFixedSize(field_size.width() * 11, field_size.height() * 11);
    setSymbols(field_size);
    setDigits(field_size);
    setFields(field_size);
    this->setLayout(grid);
}

void GridWidget::setAroundShipFields(const QVector<QPair<int, int>> &coordinates) {
    //QImage("/home/vitaly/QtProject/BattleShips/images/field/around_field.jpg").scaled(size).save("/home/vitaly/QtProject/BattleShips/images/field/around_field.jpg");
    for(const auto& i : coordinates) {
        buttons_sea_fieald[i.first + i.second * 10]->setEnabled(false);
        buttons_sea_fieald[i.first + i.second * 10]->setStyleSheet("background-color: grey;\
                                                                    border-style: outset;\
                                                                    border-width: 2px;\
                                                                    border-color: beige;");
    }
}

QPushButton** GridWidget::getField() { return  buttons_sea_fieald; }
size_t GridWidget::getFieldCount() { return field_count; }

void GridWidget::setMissOnField(const QPair<int, int> &pos) {
    buttons_sea_fieald[pos.first + pos.second * 10]->setIcon(QPixmap("/home/vitaly/QtProject/BattleShips/images/miss.png"));
}

void GridWidget::setHitOnField(const QPair<int, int> &pos) {
    buttons_sea_fieald[pos.first + pos.second * 10]->setIcon(QPixmap("/home/vitaly/QtProject/BattleShips/images/x.png"));
}

void GridWidget::setFieldsOnShipPosition(const QVector<QPair<int, int>> &pos, bool orientation) {
    setFieldPixOnShipPositionInGrid(pos, orientation);
}

void GridWidget::setNewWidgetSize(const QSize & size) {
    this->setFixedSize(size.width(), size.height());
}

void GridWidget::setNewFieldSize(const QSize & size) {
    for (size_t i = 0; i < field_count; ++i)
        buttons_sea_fieald[i]->setFixedSize(size);
}
void GridWidget::setNewSymbolsSize(const QSize & size){
    for (int i = 1; i <= 10; ++i)
    {
        QImage("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".png").scaled(size).save("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".png");
        QPixmap pix("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".png");
        symbols[i - 1] = pix;
        symbol_label[i - 1]->setPixmap(symbols[i - 1]);
        symbol_label[i - 1]->setFixedSize(size);
    }
}
void GridWidget::setNewDigitsSize(const QSize & size){
    for (int i = 1; i <= 10; ++i)
    {
        QImage("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png").scaled(size).save("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
        QPixmap pix("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
        digit[i - 1] = pix;
        digit_label[i - 1]->setPixmap(digit[i - 1]);
        digit_label[i - 1]->setFixedSize(size);
        grid->addWidget(digit_label[i - 1], i, 0, Qt::AlignCenter);
    }
}

void GridWidget::setShipPositionInGrid(const QPair<int, int> &pos, bool orientation, int length)
{
    //qDebug() << "setShipPositionInGrid:";
    if (orientation) {
        for(int i = 0; i < length; ++i) {
             buttons_sea_fieald[pos.first + 10 * pos.second + i]->setIcon(QPixmap());
             buttons_sea_fieald[pos.first + 10 * pos.second + i]->setStyleSheet("background-color: black;\
                                                                                 border-style: outset;\
                                                                                 border-width: 2px;\
                                                                                 border-color: beige;");
        }
    }
    else {
        for(int i = 0; i < length; ++i) {
             buttons_sea_fieald[pos.first + 10 * pos.second + i * 10]->setIcon(QPixmap());
             buttons_sea_fieald[pos.first + 10 * pos.second + i * 10]->setStyleSheet("background-color: black;\
                                                                                      border-style: outset;\
                                                                                      border-width: 2px;\
                                                                                      border-color: beige;");
        }
    }
}

void GridWidget::setFieldPixOnShipPositionInGrid(const QVector<QPair<int, int>> &pos, bool orientation)
{
    if (orientation) {
        for(int i = 0; i < pos.size(); ++i) {
//             buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setIcon(*field);
            buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setStyleSheet("background-color: blue;\
                                                                                      border-style: outset;\
                                                                                      border-width: 2px;\
                                                                                      border-color: beige;");
             buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setIconSize(QSize(80, 80));
             buttons_sea_fieald[pos[0].first + 10 * pos[i].second + i]->setFlat(false);
        }
    }
    else {
        for(int i = 0; i < pos.size(); ++i) {
             //buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setIcon(*field);
            buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setStyleSheet("background-color: blue;\
                                                                                      border-style: outset;\
                                                                                      border-width: 2px;\
                                                                                      border-color: beige;");
             buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setIconSize(QSize(80, 80));
             buttons_sea_fieald[pos[i].first + 10 * pos[0].second + i * 10]->setFlat(false);
        }
    }
}

size_t GridWidget::findFieldNumber(QPushButton *button)
{
    for(size_t i = 0; i < field_count; ++i)
        if(buttons_sea_fieald[i] == button)
            return i;
    return -1;
}

void GridWidget::setFields(const QSize & size)
{
    for (size_t i = 0; i < field_count; ++i)
    {
//        buttons_sea_fieald[i] = new QPushButton(*field, "", this);
        buttons_sea_fieald[i] = new QPushButton(this);
        buttons_sea_fieald[i]->setStyleSheet("background-color: blue;\
                                             border-style: outset;\
                                             border-width: 2px;\
                                             border-color: beige;");
        buttons_sea_fieald[i]->setIconSize(size);
        buttons_sea_fieald[i]->setFlat(false);
        buttons_sea_fieald[i]->setFixedSize(size);
        grid->addWidget(buttons_sea_fieald[i], 1 + i / 10, 1 + i % 10, Qt::AlignCenter);
    }
}

void GridWidget::setGameFields()
{
    for (size_t i = 0; i < field_count; ++i)
    {
        buttons_sea_fieald[i] = new QPushButton(*field, "", this);
        //buttons_sea_fieald[i]->setIconSize(QSize(80, 80));
        buttons_sea_fieald[i]->setFlat(false);
        buttons_sea_fieald[i]->setFixedSize(QSize(80, 80));
        grid->addWidget(buttons_sea_fieald[i], 1 + i / 10, 1 + i % 10, Qt::AlignCenter);
    }
}

void GridWidget::setSymbols(const QSize & size)
{
    for (int i = 1; i <= 10; ++i)
    {
        QImage("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".png").scaled(size).save("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".png");
        QPixmap pix("/home/vitaly/QtProject/BattleShips/images/symbols/" + QString::number(i) + ".png");
        symbols.push_back(pix);
        symbol_label[i - 1] = new QLabel(this);
        symbol_label[i - 1]->setPixmap(symbols[i - 1]);
        symbol_label[i - 1]->setFixedSize(size);
        symbol_label[i - 1]->setAttribute(Qt::WA_TranslucentBackground);
        grid->addWidget(symbol_label[i - 1], 0, i, Qt::AlignCenter);
    }
}

void GridWidget::setDigits(const QSize & size)
{
    for (int i = 1; i <= 10; ++i)
    {
        QImage("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png").scaled(80, 80).save("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
        QPixmap pix("/home/vitaly/QtProject/BattleShips/images/digits/" + QString::number(i) + ".png");
        digit_label[i - 1] = new QLabel(this);
        digit.push_back(pix);
        digit_label[i - 1]->setPixmap(digit[i - 1]);
        digit_label[i - 1]->setFixedSize(size);
        digit_label[i - 1]->setAttribute(Qt::WA_TranslucentBackground);
        grid->addWidget(digit_label[i - 1], i, 0, Qt::AlignCenter);
    }
}


GridWidget::~GridWidget() {
    delete grid;
    delete field;

    for (size_t i = 0; i < field_count; ++i)
        delete buttons_sea_fieald[i];
}
