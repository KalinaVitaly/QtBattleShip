#include "BattleGameWidget.h"
#include <QDebug>

BattleGameWidget::BattleGameWidget(Player *pl, std::array<std::array<int, 10>, 10> player_field, QWidget *parent) : QWidget(parent)
{
    //this->setFixedSize(1800, 1000);
    h_layout = new QHBoxLayout(this);
    motions_layout = new QHBoxLayout;
    enemy_field = new GridWidget(QSize(80, 80));
    player_ships = new GridLabelWidget(player_field, QSize(40, 40));
    v_layout = new QVBoxLayout;
    pause = new QPushButton("Pause");
    game_state = new QLabel("Your move");
    player_motions = new QLabel;
    enemy_motions = new QLabel;
    game_logic = new GameLogic(pl);

    pause->setStyleSheet("background-color : red;\
                          border : 2px solid black;\
                          border-radius : 5px;");
    game_state->setStyleSheet("background-color : white;\
                               border : 2px solid black;\
                               border-radius : 5px;");

    game_state->setFixedSize(QSize(640, 40));

    motions_layout->addWidget(player_motions);
    motions_layout->addWidget(enemy_motions);
    h_layout->addWidget(enemy_field);
    v_layout->addWidget(pause);
    v_layout->addWidget(game_state);
    v_layout->addLayout(motions_layout);
    v_layout->addWidget(player_ships);
    h_layout->addLayout(v_layout);

    connectButtonsWithGameLogic();
}

void BattleGameWidget::getButtonFieldClickedAndAddCoordinates() {
   int number = enemy_field->findFieldNumber((QPushButton*)sender());
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;
    emit fieldClicked(position);
}

void BattleGameWidget::connectButtonsWithGameLogic() {

    for (size_t i = 0; i < enemy_field->getFieldCount(); ++i) {
        QObject::connect(enemy_field->getField()[i], SIGNAL(clicked()),
                this, SLOT(getButtonFieldClickedAndAddCoordinates()));
    }

    QObject::connect(this, SIGNAL(fieldClicked(const QPair<int, int> &)),
                     game_logic, SLOT(setShootFromGrid(const QPair<int, int> &)));

    QObject::connect(game_logic, SIGNAL(setBombMiss(const QPair<int, int> &)),
                     enemy_field, SLOT(setMissOnField(const QPair<int, int> &)));
    QObject::connect(game_logic, SIGNAL(setBombHit(const QPair<int, int> &)),
                     enemy_field, SLOT(setHitOnField(const QPair<int, int> &)));
}

BattleGameWidget::~BattleGameWidget() {
    delete game_logic;
    delete player_ships;
}
