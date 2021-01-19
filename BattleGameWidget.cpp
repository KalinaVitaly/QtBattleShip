#include "BattleGameWidget.h"
#include <QDebug>

BattleGameWidget::BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent) : QWidget(parent)
{
    //this->setFixedSize(1800, 1000);
    h_layout = new QHBoxLayout(this);
    motions_layout = new QHBoxLayout;
    grid_button_enemy_fields = new GridWidget(QSize(80, 80));
    grid_label_player_fields = new GridLabelWidget(player_field, QSize(40, 40));
    v_layout = new QVBoxLayout;
    pause = new QPushButton("Pause");
    game_state = new QLabel("Your move");
    player_motions = new QLabel;
    enemy_motions = new QLabel;
    game_logic = new GameLogicWithComputer(pl);

    pause->setStyleSheet("background-color : red;\
                          border : 2px solid black;\
                          border-radius : 5px;");
    game_state->setStyleSheet("background-color : white;\
                               border : 2px solid black;\
                               border-radius : 5px;");
    this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                         stop : 0 #3EADCF, stop: 1 #ABE9CD);");

    game_state->setAttribute(Qt::WA_TranslucentBackground);
    game_state->setFixedSize(QSize(640, 40));
    pause->setAttribute(Qt::WA_TranslucentBackground);

    motions_layout->addWidget(player_motions);
    motions_layout->addWidget(enemy_motions);
    h_layout->addWidget(grid_button_enemy_fields);
    v_layout->addWidget(pause);
    //v_layout->addStretch(0);
    v_layout->addWidget(game_state);
    //v_layout->addStretch(0);
    //v_layout->addLayout(motions_layout);
    v_layout->addWidget(grid_label_player_fields);
    h_layout->addLayout(v_layout);

    connectButtonsWithGameLogic();
}

void BattleGameWidget::getCoordinatesButtonClicked(QPushButton * field) {
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
}

void BattleGameWidget::getSignalEndGame(const QString & information) {
    result_menu = new ResultMenu(information);

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
    hide();
    result_menu->hide();
}

void BattleGameWidget::retryButtonClicked() {
    //add new game
    PreparationGameWidget *game_widget = new PreparationGameWidget;
    game_widget->show();
    hide();
    result_menu->hide();
}


void BattleGameWidget::connectButtonsGridWithGameLogic() {
    for (size_t i = 0; i < grid_button_enemy_fields->getFieldCount(); ++i) {
//        QObject::connect(grid_button_enemy_fields->getField()[i], SIGNAL(clicked()),
//                this, SLOT(getCoordinatesButtonClicked()));
        QObject::connect(grid_button_enemy_fields->getField()[i], SIGNAL(clicked()),
                game_logic, SLOT(signalProcessing()));
        QObject::connect(game_logic, SIGNAL(playerClickedField(QPushButton *)),
                this, SLOT(getCoordinatesButtonClicked(QPushButton *)));
    }
}



BattleGameWidget::~BattleGameWidget() {
    delete h_layout;
    delete motions_layout;
    delete grid_button_enemy_fields;
    delete v_layout;
    delete pause;
    delete game_state;
    delete player_motions;
    delete enemy_motions;
    delete game_logic;
    delete grid_label_player_fields;
}
