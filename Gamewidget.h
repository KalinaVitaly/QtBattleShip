#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include "Ship.h"
#include "Player.h"
#include "Gridwidget.h"
#include "ShipsWidget.h"

class GameWidget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *grid;
    QHBoxLayout *horizantal_layout;
    QVBoxLayout *vertical_layout;
    QRadioButton *prad_vertical;
    QRadioButton *prad_horizantal;
    QPushButton *buttons_sea_fieald[100];
    QPixmap *field;
    GridWidget *grid_widget;
    ShipsWidget *ships_and_digits;

    Player player1;             //current player
    Player player2;             //enimy player
    const size_t fields_count;

    enum game_state {
        wait_enemy_motion,
        player_motion,
        pause
    };

    void connectFielButtondWithFieldClicked();
//    void setButtonParams(QPushButton *&button, const QSize &size, QPixmap *pix);
//    void setShipButtonParams(QPushButton *&button, QLabel *&digit, QHBoxLayout *&layout,
//                             QPalette &palette, const QSize &size, QPixmap *pixship, QPixmap *pixdigit);
//    size_t getOccupiedShipField();
//    size_t getNumberClickField(QPushButton *button);
//    QLabel* getLabelShip(const QPushButton *button);
//    QPixmap* getPixMapDigit(int digit);

public:
    explicit GameWidget(QWidget *parent = nullptr);
    //~GameWidget();

    //void
private slots:
    void fieldClicked();
//    void processingKeyboardClicks();
//    void shipClicked();
//    void putShipInPosition();
};


#endif // GAMEWIDGET_H
