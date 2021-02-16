#include "GridButtonWidget.h"
#include <QDebug>

GridWidget::GridWidget(QSize field_size, QWidget *parent)
    : QWidget(parent),
      gridLayout(new QGridLayout(this)),
      symbolLabel(10),
      digitLabel(10),
      fieldsCount(100),
      size(field_size)
{
    setFixedSize(field_size.width() * 11, field_size.height() * 11);
    setupSymbols(field_size);
    setupDigits(field_size);
    setupFields(field_size);
    setLayout(gridLayout);
}

void GridWidget::slotSetAroundShipFields(const QVector<QPair<int, int>> &coordinates) {
    for(const auto& i : coordinates) {
        buttonsSeaFiealds[i.first + i.second * 10]->setButtonState("UNKNOWN_FIELD");
    }
}

Button** GridWidget::getField() { return  buttonsSeaFiealds; }

size_t GridWidget::getFieldCount() { return fieldsCount; }

void GridWidget::slotSetMissOnField(const QPair<int, int> &pos) {
    buttonsSeaFiealds[pos.first + pos.second * 10]->setButtonState("MISS_FIELD");
}

void GridWidget::slotSetHitOnField(const QPair<int, int> &pos) {
    buttonsSeaFiealds[pos.first + pos.second * 10]->setButtonState("DESTROYEDED_FIELD");
}

void GridWidget::slotSetFieldsOnShipPosition(const QVector<QPair<int, int>> &pos, bool orientation) {
    if (orientation) {
        for(int i = 0; i < pos.size(); ++i) {
            buttonsSeaFiealds[pos[0].first + 10 * pos[i].second + i]->setButtonState("EMPTY_FIELD");
        }
    } else {
        for(int i = 0; i < pos.size(); ++i) {
            buttonsSeaFiealds[pos[i].first + 10 * pos[0].second + i * 10]->setButtonState("EMPTY_FIELD");
        }
    }
}

void GridWidget::setShipPositionInGrid(const QPair<int, int> &pos, bool orientation, int length)
{
    if (orientation) {
        for(int i = 0; i < length; ++i) {
             buttonsSeaFiealds[pos.first + 10 * pos.second + i]->setButtonState("SHIP_FIELD");
        }
    } else {
        for(int i = 0; i < length; ++i) {
             buttonsSeaFiealds[pos.first + 10 * pos.second + i * 10]->setButtonState("SHIP_FIELD");
        }
    }
}

size_t GridWidget::findFieldNumber(Button *button)
{
    for(size_t i = 0; i < fieldsCount; ++i)
        if(buttonsSeaFiealds[i] == button)
            return i;
    return -1;
}

void GridWidget::setupFields(const QSize & size)
{
    for (size_t i = 0; i < fieldsCount; ++i)
    {
        buttonsSeaFiealds[i] = new Button(this);
        buttonsSeaFiealds[i]->setFixedSize(size);
        gridLayout->addWidget(buttonsSeaFiealds[i], 1 + i / 10, 1 + i % 10, Qt::AlignCenter);
    }
}

void GridWidget::setGameFields()
{
    for (size_t i = 0; i < fieldsCount; ++i)
    {
        buttonsSeaFiealds[i] = new Button(this);
        buttonsSeaFiealds[i]->setFixedSize(QSize(80, 80));
        gridLayout->addWidget(buttonsSeaFiealds[i], 1 + i / 10, 1 + i % 10, Qt::AlignCenter);
    }
}

void GridWidget::setupSymbols(const QSize & size)
{
    QFont font("New Century Schoolbook");
    font.setPointSize(30);
    for (int i = 1; i <= 10; ++i) {
        symbolLabel[i - 1] = new QLabel(this);
        symbolLabel[i - 1]->setText(QString('A' + i - 1));
        symbolLabel[i - 1]->setAlignment(Qt::AlignCenter);
        symbolLabel[i - 1]->setFixedSize(size);
        symbolLabel[i - 1]->setAttribute(Qt::WA_TranslucentBackground);
        symbolLabel[i - 1]->setFont(font);
        gridLayout->addWidget(symbolLabel[i - 1], 0, i, Qt::AlignCenter);
    }
}

void GridWidget::setupDigits(const QSize & size)
{
    for (int i = 1; i <= 10; ++i) {
        QFont font("New Century Schoolbook");
        font.setPointSize(30);
        digitLabel[i - 1] = new QLabel(this);
        digitLabel[i - 1]->setText(QString::number(i));
        digitLabel[i - 1]->setFont(font);
        digitLabel[i - 1]->setAlignment(Qt::AlignCenter);
        digitLabel[i - 1]->setFixedSize(size);
        digitLabel[i - 1]->setAttribute(Qt::WA_TranslucentBackground);
        gridLayout->addWidget(digitLabel[i - 1], i, 0, Qt::AlignCenter);
    }
}


GridWidget::~GridWidget() {
    for (size_t i = 0; i < fieldsCount; ++i)
        delete buttonsSeaFiealds[i];
}
