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
    QVBoxLayout *vertical_layout;
    QHBoxLayout *horiz_layout1;
    QHBoxLayout *horiz_layout2;
    QHBoxLayout *horiz_layout3;
    QHBoxLayout *horiz_layout4;
    QMap<int, int> have_ships;
    QMap<int, QLabel *> *label_digits;
    QMap<int, QPushButton *> *button_ships;
    QMap<int, QPixmap *> *pix_digit;
    QMap<int, QPixmap *> *pix_ship;

    int choose_ship_type;
    void setButtonAndLabel(QHBoxLayout *&layout, QPushButton *&button, QLabel *&label, QPixmap *&pix, QPixmap *&pix2, int i);
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
    void shipClicked();

public slots:
    void setMax();
    void setNulls();
    
signals:
    void showStartGame();
    void hideStartGame();
};

#endif // SHIPSWIDGET_H
