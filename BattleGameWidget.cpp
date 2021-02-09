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
    //this->setFixedSize(1800, 1000);

    setStyleSheets();

    pauseButton->setAttribute(Qt::WA_TranslucentBackground);
    mainLayout->addWidget(gridButtonsEnemyFields);
    v_layout->addWidget(startGameButton);
    v_layout->addWidget(pauseButton);
    v_layout->addWidget(gridLabelPlayerFields);
    mainLayout->addLayout(v_layout);

    connect(startGameButton, SIGNAL(clicked()),
            this, SLOT(startGameClicked()));
}

void BattleGameWidget::startGameClicked() {
    connectButtonsWithGameLogic();

    startGameButton->deleteLater();

//    bool first_player_begin_game = rand() % 2;

//    if (first_player_begin_game) {
//        connect(this, SIGNAL(signalStartGame()),
//                player1, )
//    }

//    emit signalStartGame();
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

void BattleGameWidget::getCoordinatesButtonClicked(Button * field) {
    int number = gridButtonsEnemyFields->findFieldNumber(field);
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;
    emit buttonFieldClicked(position);
}

void BattleGameWidget::connectButtonsWithGameLogic() {
    qDebug() << "connectButtonsWithGameLogic";
    connectButtonsGridWithGameLogic();

    QObject::connect(this, SIGNAL(buttonFieldClicked(const QPair<int, int> &)),
                     gameLogic, SLOT(setShootFromGrid(const QPair<int, int> &)));

    QObject::connect(gameLogic, SIGNAL(setBombMiss2LabelGrid(const QPair<int, int> &)),
                     gridButtonsEnemyFields, SLOT(setMissOnField(const QPair<int, int> &)));
    QObject::connect(gameLogic, SIGNAL(setBombHit2LabelGrid(const QPair<int, int> &)),
                     gridButtonsEnemyFields, SLOT(setHitOnField(const QPair<int, int> &)));

    QObject::connect(gameLogic, SIGNAL(setBombMissFromComputer(const QPair<int, int> &)),
                     gridLabelPlayerFields, SLOT(setBombMissOnLabelGrid(const QPair<int, int> &)));
    QObject::connect(gameLogic, SIGNAL(setBombHitFromComputer(const QPair<int, int> &)),
                     gridLabelPlayerFields, SLOT(setBombHitOnLabelGrid(const QPair<int, int> &)));

    QObject::connect(gameLogic, SIGNAL(setAroundDestroyededShipInactiveFields(const QVector<QPair<int, int>> &)),
                     gridButtonsEnemyFields, SLOT(setAroundShipFields(const QVector<QPair<int, int>> &)));
    QObject::connect(gameLogic, SIGNAL(setAroundDestroyededPlayerShipFields(const QVector<QPair<int, int>> &)),
                     gridLabelPlayerFields, SLOT(setFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> &)));

    QObject::connect(gameLogic, SIGNAL(signalEndGame(const QString &)),
                     this, SLOT(getSignalEndGame(const QString &)));

    QObject::connect(pauseButton, SIGNAL(clicked()),
                     this, SLOT(getSignalEndGame()));
}

void BattleGameWidget::getSignalEndGame(const QString & information) {
    resultMenuWidget = new GameMenu(information);

    QObject::connect(resultMenuWidget->getButtonExit(), SIGNAL(clicked()),
                     this, SLOT(exitButtonClicked()));

    QObject::connect(resultMenuWidget->getButtonRetryGame(), SIGNAL(clicked()),
                     this, SLOT(retryButtonClicked()));

    resultMenuWidget->show();
}

void BattleGameWidget::exitButtonClicked() {
    //add main menu
    MainWindow *main_window = new MainWindow;
    main_window->show();

    this->close();
    resultMenuWidget->close();
}

void BattleGameWidget::retryButtonClicked() {
    //add new game
    PreparationGameWidget *game_widget = new PreparationGameWidget;
    game_widget->show();

    deleteLater();
    resultMenuWidget->deleteLater();
}


void BattleGameWidget::connectButtonsGridWithGameLogic() {
    for (size_t i = 0; i < gridButtonsEnemyFields->getFieldCount(); ++i) {
//        QObject::connect(grid_button_enemy_fields->getField()[i], SIGNAL(clicked()),
//                this, SLOT(getCoordinatesButtonClicked()));
        QObject::connect(gridButtonsEnemyFields->getField()[i], SIGNAL(signalClicked()),
                gameLogic, SLOT(signalProcessing()));
        QObject::connect(gameLogic, SIGNAL(playerClickedField(Button *)),
                this, SLOT(getCoordinatesButtonClicked(Button *)));
    }
}



BattleGameWidget::~BattleGameWidget() {
    delete gameLogic;
}
