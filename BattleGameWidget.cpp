#include "BattleGameWidget.h"

BattleGameWidget::BattleGameWidget(GridWidget *_player_field, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1800, 1000);
    h_layout = new QHBoxLayout(this);
    player_field = _player_field;
    enemy_field = new GridWidget;

    h_layout->addWidget(enemy_field);
    h_layout->addWidget(player_field);
}
