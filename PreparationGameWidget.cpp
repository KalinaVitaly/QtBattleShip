#include "PreparationGameWidget.h"
#include <QDebug>

PreparationGameWidget::PreparationGameWidget(QWidget *parent) :
    QWidget(parent),
    horizantal_layout(new QHBoxLayout(this)),
    //vertical_layout(new QVBoxLayout(this)),
    grid_widget(new GridWidget(QSize(80, 80), this)),
    ships_and_digits(new ShipsWidget(this)),
    rbapb(new RadioButtonsAndPushButtons(this)),
    player1(new Player),
    fields_count(100),
    orientation(true)
{
    //grid widget 880*880
    //this->setFixedSize(1800, 1000);

    horizantal_layout->addWidget(grid_widget);
    horizantal_layout->addWidget(ships_and_digits);
    horizantal_layout->addWidget(rbapb);

    this->setLayout(horizantal_layout);
    this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                         stop : 0 #3EADCF, stop: 1 #ABE9CD);");

    connectFielButtondWithFieldClicked();

    //connect radioButtons with orientation
    QObject::connect(rbapb->getVertical(), SIGNAL(clicked()),
                     this, SLOT(radioButtonClicked()));
    QObject::connect(rbapb->getHorizantal(), SIGNAL(clicked()),
                     this, SLOT(radioButtonClicked()));
    //connect button start
    QObject::connect(ships_and_digits, SIGNAL(showStartGame()),
                     this, SLOT(activateStartButton()));
    QObject::connect(ships_and_digits, SIGNAL(hideStartGame()),
                     this, SLOT(diactivateStartButton()));
    QObject::connect(rbapb->getAutoPlacementShips(), SIGNAL(clicked()),
                     this, SLOT(autoPlacementShipsClicked()));

    //connect player with grid widget
    QObject::connect(player1, &Player::deleteShipFromFields,
                     grid_widget, &GridWidget::setFieldsOnShipPosition);
    QObject::connect(this, &PreparationGameWidget::setNullsShipsAndWidget,
                     ships_and_digits, &ShipsWidget::setNulls);
    QObject::connect(this, &PreparationGameWidget::setMaxShipsAndWidget,
                     ships_and_digits, &ShipsWidget::setMax);
}

void PreparationGameWidget::autoPlacementShipsClicked() {
    if ((player1->getShipCount(1) + player1->getShipCount(2) + player1->getShipCount(3) + player1->getShipCount(4)) == 10) {
        player1->deleteAllShips();
        emit setMaxShipsAndWidget();
    }
    AutomaticShipsPlacement::setRandomPositionShips(player1, grid_widget, ships_and_digits);
    emit setNullsShipsAndWidget();
}

void PreparationGameWidget::startGameClicked() {
    Button **button = grid_widget->getField();

    for(size_t i = 0; i < grid_widget->getFieldCount(); ++i)
        QObject::disconnect(button[i], SIGNAL(signalClicked()),
                         this, SLOT(fieldClicked()));

    BattleGameWidget *bgw = new BattleGameWidget(player1, player1->getField());
    bgw->show();

    this->close();
//    this->hide();

//    this->deleteLater();
}

void PreparationGameWidget::diactivateStartButton() {
    rbapb->getStart()->setStyleSheet("QPushButton {\
                                      color : black;\
                                      background: rgba(255,255,255,100);\
                                      font-family: New Century Schoolbook;\
                                      border-style: outset;\
                                      border-width: 2px;\
                                      border-color: beige;\
                                      font-size : 20px;\
                                      border-radius: 10px;\
                                      }");
    rbapb->getStart()->setToolTip("To start the game you need to place all the ships.");
    QObject::disconnect(rbapb->getStart(), SIGNAL(clicked()),
                     this, SLOT(startGameClicked()));
}

void PreparationGameWidget::activateStartButton() {
    rbapb->getStart()->setStyleSheet("QAbstractButton {\
                                     color : black;\
                                     background: red;\
                                     font-family: New Century Schoolbook;\
                                     font-size : 20px;\
                                     border-style: outset;\
                                     border-width: 2px;\
                                     border-color: beige;\
                                     border-radius: 10px;\
                                     }\
                                     QPushButton:pressed {\
                                     background-color : #B2BEB5\
                                     }");
    rbapb->getStart()->setToolTip("");
    QObject::connect(rbapb->getStart(), SIGNAL(clicked()),
                     this, SLOT(startGameClicked()));
}

void PreparationGameWidget::radioButtonClicked() {
   if (rbapb->getVertical() == sender()) {
       orientation = false;
   }
   else if (rbapb->getHorizantal() == sender()) {
       orientation = true;
   }
}

void PreparationGameWidget::connectFielButtondWithFieldClicked() {
    Button **button = grid_widget->getField();
    for(size_t i = 0; i < grid_widget->getFieldCount(); ++i)
        QObject::connect(button[i], SIGNAL(signalClicked()),
                         this, SLOT(fieldClicked()));
}

void PreparationGameWidget::fieldClicked() {
    int number = grid_widget->findFieldNumber((Button*)sender());
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;

    QCursor *current_global_cursor = (QApplication::overrideCursor());
    if (current_global_cursor != 0 && *(QApplication::overrideCursor()) == Qt::ClosedHandCursor)
    {
        QVector<QPair<int, int>> coordinates = player1->convertPointAndOrientation2Coordinates(position, ships_and_digits->getClickedShipType(), orientation);
        if (player1->canSetShipOnPosition(coordinates, orientation))
        {
            player1->setShipOnPosition(coordinates, ships_and_digits->getClickedShipType(), orientation);
            grid_widget->setShipPositionInGrid(position, orientation, ships_and_digits->getClickedShipType());
            ships_and_digits->changeDigitPixMap();
            QApplication::restoreOverrideCursor();
            cursor() = Qt::ArrowCursor;
        }
    }
    else if (current_global_cursor == nullptr && (cursor() == Qt::ArrowCursor) && player1->hasShipOnPoint(position))
    {
        //qDebug() << "here";
        Ship *ship = player1->findShipByPosition(position);
        if (ship != nullptr) {
            ships_and_digits->setChooseShip(player1->findShipByPosition(position)->getShipType());
            grid_widget->setFieldPixOnShipPositionInGrid(player1->convertPointAndOrientation2Coordinates(ship->getShipbegin(), ships_and_digits->getClickedShipType(), ship->getOrientation()),
                                                         ship->getOrientation());
            player1->deleteShipFromPosition(position);
            ships_and_digits->returnChangedDigitPixMap();
            QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        }
    }
}

PreparationGameWidget::~PreparationGameWidget()
{

}
