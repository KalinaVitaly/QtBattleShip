#ifndef SHIPSWIDGET_H
#define SHIPSWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class ShipsWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizLayout1;
    QHBoxLayout *horizLayout2;
    QHBoxLayout *horizLayout3;
    QHBoxLayout *horizLayout4;
    QMap<int, int> haveShips;
    QMap<int, QLabel *> *digitsLabel;
    QMap<int, QPushButton *> *shipsButton;
    QMap<int, QPixmap *> *digitPixmap;
    QMap<int, QPixmap *> *shipPixmap;

    int chooseShipType;

    //
    // Устанавливаем корабли и их кол-во
    //
    void setButtonAndLabel(QHBoxLayout *&layout, QPushButton *&button, QLabel *&label, QPixmap *&pix, QPixmap *&pix2, int i);

    //
    // Обновляем кол-во кораблей
    //
    void updateDigits();
public:
    ShipsWidget(QWidget *parent = nullptr);
    ~ShipsWidget();

    int getClickedShipType() const;
    void changeDigitPixMap();
    void checkingBeforeGameStarting();
    void returnChangedDigitPixMap();
    void setChooseShip(int type);
    void setChooseShipType(int type);

private slots:
    void slotShipClicked();

public slots:
    void slotSetMax();
    void slotSetNulls();
    
signals:
    void signalShowStartGame();
    void signalHideStartGame();
};

#endif // SHIPSWIDGET_H
