#include "BattleGameWidget.h"

BattleGameWidget::BattleGameWidget(std::array<std::array<int, 10>, 10> player_field, QWidget *parent) : QWidget(parent)
{
    //this->setFixedSize(1800, 1000);
    h_layout = new QHBoxLayout(this);
    enemy_field = new GridWidget(QSize(80, 80));
    player_ships = new GridLabelWidget(player_field, QSize(40, 40));
    v_layout = new QVBoxLayout;
    pause = new QPushButton("Pause");
    pause->setStyleSheet("background-color : red;\
                          border : 2px solid black;\
                          border-radius : 5px;");

    h_layout->addWidget(enemy_field);
    v_layout->addWidget(pause);
    v_layout->addWidget(player_ships);
    h_layout->addLayout(v_layout);
}
