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
    QPushButton *ship1;
    QPushButton *ship2;
    QPushButton *ship3;
    QPushButton *ship4;
    QPixmap *pix_ship1;
    QPixmap *pix_ship2;
    QPixmap *pix_ship3;
    QPixmap *pix_ship4;
    QPixmap *pix_one;
    QPixmap *pix_two;
    QPixmap *pix_three;
    QPixmap *pix_four;
    QLabel *dig1;
    QLabel *dig2;
    QLabel *dig3;
    QLabel *dig4;
    int have_ship1;
    int have_ship2;
    int have_ship3;
    int have_ship4;

    int choose_ship_type;
    void setButtonAndLabel(QHBoxLayout *&layout, QPushButton *&button, QLabel *&label, QPixmap *&pix, QPixmap *&pix2);
public:
    ShipsWidget(QWidget *parent = nullptr);

    int getClickedShipType() const;
    void changeDigitPixMap();
    void checkingBeforeGameStarting();
    void returnChangedDigitPixMap();
    void setChooseShip(int type);
    void setChooseShipType(int type);

private slots:
    void shipClicked();
    
signals:
    void showStartGame();
    void hideStartGame();
};

#endif // SHIPSWIDGET_H
