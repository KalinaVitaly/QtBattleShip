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
#include "Button.h"

class PreparationGameWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *mainLayout;
    QPushButton *buttons_sea_fieald[100];
    GridWidget *gridWidget;
    ShipsWidget *shipsWidget;
    RadioButtonsAndPushButtons *rbapb;

    Player *player1;
    const size_t fieldsCount;
    bool orientation;

    //
    // Соединяем игровые поля
    //
    void connectFieldButtons();

    //
    // Соединяем кнопки интерфейса приложения
    //
    void connectButtons();

public:
    explicit PreparationGameWidget(QWidget *parent = nullptr);
    ~PreparationGameWidget() override;

private slots:
    void slotFieldClicked();
    void slotRadioButtonClicked();
    void slotActivateStartButton();
    void slotDiactivateStartButton();
    void slotStartGameClicked();
    void slotAutoPlacementShipsClicked();

signals:
    void signalSetNullsShipsAndWidget();
    void signalSetMaxShipsAndWidget();
};


#endif // GAMEWIDGET_H
