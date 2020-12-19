#ifndef BATTLEGAMEWIDGET_H
#define BATTLEGAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <array>
#include <QLabel>
#include "GameLogic.h"
#include "GridWidget.h"
#include "GridLabelWidget.h"
#include "Player.h"

class BattleGameWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *h_layout;
    QHBoxLayout *motions_layout;
    QVBoxLayout *v_layout;
    GridWidget *enemy_field;
    GridLabelWidget *player_ships;
    QPushButton *pause;
    QLabel *game_state;
    QLabel *player_motions;
    QLabel *enemy_motions;
    Player *player;
    GameLogic *game_logic;

    void connectButtonsWithGameLogic();

public:
    BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent = nullptr);
    ~BattleGameWidget();

private slots:
    void getButtonFieldClickedAndAddCoordinates();

signals:
    void fieldClicked(const QPair<int, int> &);
};

#endif // BATTLEGAMEWIDGET_H
