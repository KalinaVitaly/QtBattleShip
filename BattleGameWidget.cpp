#include "BattleGameWidget.h"
#include <QDebug>

BattleGameWidget::BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent) :
    QWidget(parent),
    h_layout(new QHBoxLayout(this)),
    motions_layout(new QHBoxLayout()),
    v_layout(new QVBoxLayout()),
    grid_button_enemy_fields(new GridWidget(QSize(80, 80), this)),
    grid_label_player_fields(new GridLabelWidget(player_field, QSize(40, 40), this)),
    pause(new QPushButton("Pause", this)),
    start_game(new QPushButton("Start game!", this)),
    game_logic(new GameLogicWithComputer(pl, this))

{
    //this->setFixedSize(1800, 1000);

    setStyleSheets();

    pause->setAttribute(Qt::WA_TranslucentBackground);
    h_layout->addWidget(grid_button_enemy_fields);
    v_layout->addWidget(start_game);
    v_layout->addWidget(pause);
    v_layout->addWidget(grid_label_player_fields);
    h_layout->addLayout(v_layout);

    connect(start_game, SIGNAL(clicked()),
            this, SLOT(startGameClicked()));
}

void BattleGameWidget::startGameClicked() {
    connectButtonsWithGameLogic();
    start_game->hide();
    start_game->deleteLater();

//    bool first_player_begin_game = rand() % 2;

//    if (first_player_begin_game) {
//        connect(this, SIGNAL(signalStartGame()),
//                player1, )
//    }

//    emit signalStartGame();
}

void BattleGameWidget::setStyleSheets() {
    start_game->setStyleSheet("QPushButton {\
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

    pause->setStyleSheet("QPushButton {\
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
    int number = grid_button_enemy_fields->findFieldNumber(field);
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;
    emit buttonFieldClicked(position);
}

void BattleGameWidget::connectButtonsWithGameLogic() {
    qDebug() << "connectButtonsWithGameLogic";
    connectButtonsGridWithGameLogic();

    QObject::connect(this, SIGNAL(buttonFieldClicked(const QPair<int, int> &)),
                     game_logic, SLOT(setShootFromGrid(const QPair<int, int> &)));

    QObject::connect(game_logic, SIGNAL(setBombMiss2LabelGrid(const QPair<int, int> &)),
                     grid_button_enemy_fields, SLOT(setMissOnField(const QPair<int, int> &)));
    QObject::connect(game_logic, SIGNAL(setBombHit2LabelGrid(const QPair<int, int> &)),
                     grid_button_enemy_fields, SLOT(setHitOnField(const QPair<int, int> &)));

    QObject::connect(game_logic, SIGNAL(setBombMissFromComputer(const QPair<int, int> &)),
                     grid_label_player_fields, SLOT(setBombMissOnLabelGrid(const QPair<int, int> &)));
    QObject::connect(game_logic, SIGNAL(setBombHitFromComputer(const QPair<int, int> &)),
                     grid_label_player_fields, SLOT(setBombHitOnLabelGrid(const QPair<int, int> &)));

    QObject::connect(game_logic, SIGNAL(setAroundDestroyededShipInactiveFields(const QVector<QPair<int, int>> &)),
                     grid_button_enemy_fields, SLOT(setAroundShipFields(const QVector<QPair<int, int>> &)));
    QObject::connect(game_logic, SIGNAL(setAroundDestroyededPlayerShipFields(const QVector<QPair<int, int>> &)),
                     grid_label_player_fields, SLOT(setFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> &)));

    QObject::connect(game_logic, SIGNAL(signalEndGame(const QString &)),
                     this, SLOT(getSignalEndGame(const QString &)));

    QObject::connect(pause, SIGNAL(clicked()),
                     this, SLOT(getSignalEndGame()));
}

void BattleGameWidget::getSignalEndGame(const QString & information) {
    result_menu = new GameMenu(information);

    QObject::connect(result_menu->getButtonExit(), SIGNAL(clicked()),
                     this, SLOT(exitButtonClicked()));

    QObject::connect(result_menu->getButtonRetryGame(), SIGNAL(clicked()),
                     this, SLOT(retryButtonClicked()));

    result_menu->show();
}

void BattleGameWidget::exitButtonClicked() {
    //add main menu
    MainWindow *main_window = new MainWindow;
    main_window->show();

    this->close();
    result_menu->close();
//    hide();
//    result_menu->hide();

//    this->deleteLater();
//    result_menu->deleteLater();
}

void BattleGameWidget::retryButtonClicked() {
    //add new game
    PreparationGameWidget *game_widget = new PreparationGameWidget;
    game_widget->show();

    this->close();
    result_menu->close();

//    hide();
//    result_menu->hide();

//    this->deleteLater();
//    result_menu->deleteLater();
}


void BattleGameWidget::connectButtonsGridWithGameLogic() {
    for (size_t i = 0; i < grid_button_enemy_fields->getFieldCount(); ++i) {
//        QObject::connect(grid_button_enemy_fields->getField()[i], SIGNAL(clicked()),
//                this, SLOT(getCoordinatesButtonClicked()));
        QObject::connect(grid_button_enemy_fields->getField()[i], SIGNAL(signalClicked()),
                game_logic, SLOT(signalProcessing()));
        QObject::connect(game_logic, SIGNAL(playerClickedField(Button *)),
                this, SLOT(getCoordinatesButtonClicked(Button *)));
    }
}



BattleGameWidget::~BattleGameWidget() {
//    delete h_layout;
//    delete motions_layout;
//    delete grid_button_enemy_fields;
//    delete v_layout;
//    delete pause;
    delete game_logic;
//    delete grid_label_player_fields;
}
