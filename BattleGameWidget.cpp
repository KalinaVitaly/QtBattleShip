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

    game_state->setFixedSize(QSize(640, 40));

    motions_layout->addWidget(player_motions);
    motions_layout->addWidget(enemy_motions);
    h_layout->addWidget(grid_button_enemy_fields);
    v_layout->addWidget(pause);
    v_layout->addWidget(game_state);
    v_layout->addLayout(motions_layout);
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

}
void BattleGameWidget::connectButtons() {
    connectButtonsGridWithGameLogic();
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

void BattleGameWidget::disconnectButtonsGridWithGameLogic() {
    for (size_t i = 0; i < grid_button_enemy_fields->getFieldCount(); ++i) {
        disconnect(grid_button_enemy_fields->getField()[i], SIGNAL(clicked()),
                this, SLOT(getCoordinatesButtonClicked()));
    }
}

BattleGameWidget::~BattleGameWidget() {
    delete game_logic;
    delete grid_label_player_fields;
}
