#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class GridWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *grid;
    QPixmap *field;
    QVector<QPixmap *> symbols;
    QVector<QPixmap *> digit;
    QPushButton *buttons_sea_fieald[100];
    const size_t field_count;

    void setSymbols();
    void setDigits();
    void setFields();
public:
    GridWidget(QWidget *parent = nullptr);

    QPushButton** getField();
    size_t getFieldCount();
    size_t findFieldNumber(QPushButton *button);
    void setShipPositionInGrid(const QPair<int, int> &pos, bool orientation, int length);
};

#endif // GRIDWIDGET_H
