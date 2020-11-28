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


public:
    explicit GameWidget(QWidget *parent = nullptr);

private slots:
    void fieldClicked();

};


#endif // GAMEWIDGET_H
