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
#include "GridButtonWidget.h"
#include "ShipsWidget.h"
#include "RadioButtonsAndPushButtons.h"
#include "AutomaticShipsPlacement.h"
#include "BattleGameWidget.h"

class PreparationGameWidget : public QWidget
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
    RadioButtonsAndPushButtons *rbapb;

    Player *player1;             //current player
    const size_t fields_count;
    bool orientation;

    void connectFielButtondWithFieldClicked();


public:
    explicit PreparationGameWidget(QWidget *parent = nullptr);

private slots:
    void fieldClicked();
    void radioButtonClicked();
    void activateStartButton();
    void diactivateStartButton();
    void startGameClicked();
    void autoPlacementShipsClicked();

signals:
    void setNullsShipsAndWidget();
    void setMaxShipsAndWidget();
};


#endif // GAMEWIDGET_H
