#include "BattleGameWidget.h"
#include <QDebug>

BattleGameWidget::BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent) :
    QWidget(parent),
    mainLayout(new QHBoxLayout(this)),
    motions_layout(new QHBoxLayout()),
    v_layout(new QVBoxLayout()),
    gridButtonsEnemyFields(new GridWidget(QSize(80, 80), this)),
    gridLabelPlayerFields(new GridLabelWidget(player_field, QSize(40, 40), this)),
    pauseButton(new QPushButton("Pause", this)),
    startGameButton(new QPushButton("Start game!", this)),
    gameLogic(new GameLogicWithComputer(pl, this))

{
    setStyleSheets();

    pauseButton->setAttribute(Qt::WA_TranslucentBackground);
    mainLayout->addWidget(gridButtonsEnemyFields);
    v_layout->addWidget(startGameButton);
    v_layout->addWidget(pauseButton);
    v_layout->addWidget(gridLabelPlayerFields);
    mainLayout->addLayout(v_layout);

    connect(startGameButton, SIGNAL(clicked()),
            this, SLOT(slotStartGameClicked()));
}

void BattleGameWidget::slotStartGameClicked() {
    connectButtonsWithGameLogic();

    startGameButton->deleteLater();
}

void BattleGameWidget::setStyleSheets() {
    startGameButton->setStyleSheet("QPushButton {\
                              color : black;\
                              background: rgba(255,255,255,100);\
                              font-family: New Century Schoolbook;\
                              border-style: outset;\
                              border-width: 2px;\
                              border-color: beige;\
                              font-size : 20px;\
                              border-radius: 10px;\
                              }\
                              QPushButton:hover {\
                              background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                              stop : 0 #F8F8FF, stop: 1 #E9E9F0);\
                              }\
                              QPushButton:pressed {\
                              background-color : #B2BEB5\
                              }");

    pauseButton->setStyleSheet("QPushButton {\
                         color : black;\
                         background: rgba(255,255,255,100);\
                         font-family: New Century Schoolbook;\
                         border-style: outset;\
                         border-width: 2px;\
                         border-color: beige;\
                         font-size : 20px;\
                         border-radius: 10px;\
                         }\
                         QPushButton:hover {\
                         background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                         stop : 0 #F8F8FF, stop: 1 #E9E9F0);\
                         }\
                         QPushButton:pressed {\
                         background-color : #B2BEB5\
                         }");

    setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                         stop : 0 #3EADCF, stop: 1 #ABE9CD);");
}

void BattleGameWidget::slotGetCoordinatesButtonClicked(Button * field) {
    int number = gridButtonsEnemyFields->findFieldNumber(field);
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;
    emit signalButtonFieldClicked(position);
}

void BattleGameWidget::connectButtonsWithGameLogic() {
    connectButtonsGridWithGameLogic();

    connect(this, SIGNAL(signalButtonFieldClicked(const QPair<int, int> &)),
                     gameLogic, SLOT(slotSetShootFromGrid(const QPair<int, int> &)));

    connect(gameLogic, SIGNAL(signalSetBombMiss2LabelGrid(const QPair<int, int> &)),
                     gridButtonsEnemyFields, SLOT(slotSetMissOnField(const QPair<int, int> &)));
    connect(gameLogic, SIGNAL(signalSetBombHit2LabelGrid(const QPair<int, int> &)),
                     gridButtonsEnemyFields, SLOT(slotSetHitOnField(const QPair<int, int> &)));

    connect(gameLogic, SIGNAL(signalSetBombMissFromComputer(const QPair<int, int> &)),
                     gridLabelPlayerFields, SLOT(slotSetBombMissOnLabelGrid(const QPair<int, int> &)));
    connect(gameLogic, SIGNAL(signalSetBombHitFromComputer(const QPair<int, int> &)),
                     gridLabelPlayerFields, SLOT(slotSetBombHitOnLabelGrid(const QPair<int, int> &)));

    connect(gameLogic, SIGNAL(signalSetAroundDestroyededShipInactiveFields(const QVector<QPair<int, int>> &)),
                     gridButtonsEnemyFields, SLOT(slotSetAroundShipFields(const QVector<QPair<int, int>> &)));
    connect(gameLogic, SIGNAL(signalSetAroundDestroyededPlayerShipFields(const QVector<QPair<int, int>> &)),
                     gridLabelPlayerFields, SLOT(slotSetFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> &)));

    connect(gameLogic, SIGNAL(signalEndGame(const QString &)),
                     this, SLOT(slotGetSignalEndGame(const QString &)));

    connect(pauseButton, SIGNAL(clicked()), this, SLOT(slotGetSignalEndGame()));
}

void BattleGameWidget::slotGetSignalEndGame(const QString & information) {
    resultMenuWidget = new GameMenu(information);

    QObject::connect(resultMenuWidget->getButtonExit(), SIGNAL(clicked()),
                     this, SLOT(slotExitButtonClicked()));

    QObject::connect(resultMenuWidget->getButtonRetryGame(), SIGNAL(clicked()),
                     this, SLOT(slotRetryButtonClicked()));

    resultMenuWidget->show();
}

void BattleGameWidget::slotExitButtonClicked() {
    //add main menu
    MainWindow *main_window = new MainWindow;
    main_window->show();

    this->close();
    resultMenuWidget->close();
}

void BattleGameWidget::slotRetryButtonClicked() {
    //add new game
    PreparationGameWidget *game_widget = new PreparationGameWidget;
    game_widget->show();

    deleteLater();
    resultMenuWidget->deleteLater();
}


void BattleGameWidget::connectButtonsGridWithGameLogic() {
    for (size_t i = 0; i < gridButtonsEnemyFields->getFieldCount(); ++i) {
        connect(gridButtonsEnemyFields->getField()[i], SIGNAL(signalClicked()),
                gameLogic, SLOT(slotProcessing()));
        connect(gameLogic, SIGNAL(signalPlayerClickedField(Button *)),
                this, SLOT(slotGetCoordinatesButtonClicked(Button *)));
    }
}



BattleGameWidget::~BattleGameWidget() {
    delete gameLogic;
}
