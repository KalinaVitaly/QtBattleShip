#ifndef BATTLEGAMEWIDGET_H
#define BATTLEGAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <array>
#include <QLabel>
#include "PreparationGameWidget.h"
#include "MainMenu.h"
#include "GameLogicWithComputer.h"
#include "GridButtonWidget.h"
#include "GridLabelWidget.h"
#include "Player.h"
#include "GameMenu.h"

class BattleGameWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *h_layout;
    QHBoxLayout *motions_layout;
    QVBoxLayout *v_layout;
    GridWidget *grid_button_enemy_fields;
    GridLabelWidget *grid_label_player_fields;
    QPushButton *pause;
    Player *player;
    GameLogicWithComputer *game_logic;
    GameMenu *result_menu;

    void connectButtonsWithGameLogic();
    void connectButtonsGridWithGameLogic();
    void setStyleSheets();

public:
    BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent = nullptr);
    ~BattleGameWidget();

private slots:
    void getCoordinatesButtonClicked(QPushButton *);
    void getSignalEndGame(const QString & information = "Game Pause");
    void exitButtonClicked();
    void retryButtonClicked();

signals:
    void buttonFieldClicked(const QPair<int, int> &);
};

#endif // BATTLEGAMEWIDGET_H
