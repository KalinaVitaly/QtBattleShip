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
    QVector<QLabel *> symbol_label;
    QVector<QLabel *> digit_label;
    QPushButton *buttons_sea_fieald[100];
    const size_t field_count;
    QSize size;

    void setSymbols(const QSize & size);
    void setDigits(const QSize & size);
    void setFields(const QSize & size);
public:
    GridWidget(QSize field_size = QSize(80, 80), QWidget *parent = nullptr);
    ~GridWidget();

    QPushButton** getField();
    size_t getFieldCount();
    size_t findFieldNumber(QPushButton *button);
    void setShipPositionInGrid(const QPair<int, int> &pos, bool orientation, int length);
    void setGameFields();
    void setFieldPixOnShipPositionInGrid(const QVector<QPair<int, int>> &pos, bool orientation);

    void setNewFieldSize(const QSize & size);
    void setNewSymbolsSize(const QSize & size);
    void setNewDigitsSize(const QSize & size);
    void setNewWidgetSize(const QSize & size);

public slots:
    void setFieldsOnShipPosition(const QVector<QPair<int, int>> &pos, bool orientation);
    void setMissOnField(const QPair<int, int> &);
    void setHitOnField(const QPair<int, int> &);
    void setAroundShipFields(const QVector<QPair<int, int>> &);
};

#endif // GRIDWIDGET_H
