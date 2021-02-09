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
#include "GameLogic.h"
#include "GridButtonWidget.h"
#include "GridLabelWidget.h"
#include "Player.h"
#include "GameMenu.h"
#include "Button.h"

class BattleGameWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *mainLayout;
    QHBoxLayout *motions_layout;
    QVBoxLayout *v_layout;
    GridWidget *gridButtonsEnemyFields;
    GridLabelWidget *gridLabelPlayerFields;
    QPushButton *pauseButton;
    QPushButton *startGameButton;
    Player *player;
    GameLogicWithComputer *gameLogic;
    GameMenu *resultMenuWidget;

    void connectButtonsWithGameLogic();
    void connectButtonsGridWithGameLogic();
    void setStyleSheets();

public:
    BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent = nullptr);
    ~BattleGameWidget() override;

private slots:
    void getCoordinatesButtonClicked(Button *);
    void getSignalEndGame(const QString & information = "Game Pause");
    void exitButtonClicked();
    void retryButtonClicked();
    void startGameClicked();

signals:
    void buttonFieldClicked(const QPair<int, int> &);
    void signalStartGame();
};

#endif // BATTLEGAMEWIDGET_H
