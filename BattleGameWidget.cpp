#include "BattleGameWidget.h"

BattleGameWidget::BattleGameWidget(GridWidget *_player_field, QWidget *parent) : QWidget(parent)
{
    //this->setFixedSize(1800, 1000);
    h_layout = new QHBoxLayout(this);
    player_field = _player_field;
    QSize player_field_widgets_size = QSize(40, 40);
    enemy_field = new GridWidget(QSize(80, 80));
    player_field->setNewSymbolsSize(player_field_widgets_size);
    player_field->setNewFieldSize(player_field_widgets_size);
    player_field->setNewDigitsSize(player_field_widgets_size);
    player_field->setNewWidgetSize(QSize(player_field_widgets_size.width() * 11, player_field_widgets_size.height() * 11));

    h_layout->addWidget(enemy_field);
    h_layout->addWidget(player_field);
}
