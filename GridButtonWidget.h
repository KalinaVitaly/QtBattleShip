#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <Button.h>
#include <QGridLayout>
#include <QLabel>

class GridWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *gridLayout;
    QVector<QLabel *> symbolLabel;
    QVector<QLabel *> digitLabel;
    Button *buttonsSeaFiealds[100];
    const size_t fieldsCount;
    QSize size;

    void setupSymbols(const QSize & size);
    void setupDigits(const QSize & size);
    void setupFields(const QSize & size);
public:
    explicit GridWidget(QSize field_size = QSize(80, 80), QWidget *parent = nullptr);
    ~GridWidget() override;

    Button** getField();
    size_t getFieldCount();
    size_t findFieldNumber(Button *button);
    void setShipPositionInGrid(const QPair<int, int> &pos, bool orientation, int length);
    void setGameFields();

public slots:
    void slotSetFieldsOnShipPosition(const QVector<QPair<int, int>> &pos, bool orientation);
    void slotSetMissOnField(const QPair<int, int> &);
    void slotSetHitOnField(const QPair<int, int> &);
    void slotSetAroundShipFields(const QVector<QPair<int, int>> &);
};

#endif // GRIDWIDGET_H
