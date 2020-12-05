#ifndef BATTLEGAMEWIDGET_H
#define BATTLEGAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "GridWidget.h"

class BattleGameWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *h_layout;
    GridWidget *player_field;
    GridWidget *enemy_field;
public:
    BattleGameWidget(GridWidget *player_field, QWidget *parent = nullptr);
};

#endif // BATTLEGAMEWIDGET_H
