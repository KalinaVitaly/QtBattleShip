#ifndef BATTLEGAMEWIDGET_H
#define BATTLEGAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "GridWidget.h"
#include "GridLabelWidget.h"
#include <array>

class BattleGameWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *h_layout;
    QVBoxLayout *v_layout;
    GridWidget *enemy_field;
    GridLabelWidget *player_ships;
    QPushButton *pause;

public:
    BattleGameWidget(std::array<std::array<int, 10>, 10> player_field, QWidget *parent = nullptr);
};

#endif // BATTLEGAMEWIDGET_H
