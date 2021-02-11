#include "PreparationGameWidget.h"
#include <QDebug>

PreparationGameWidget::PreparationGameWidget(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QHBoxLayout(this)),
    gridWidget(new GridWidget(QSize(80, 80), this)),
    shipsWidget(new ShipsWidget(this)),
    rbapb(new RadioButtonsAndPushButtons(this)),
    player1(new Player),
    fieldsCount(100),
    orientation(true)
{
    mainLayout->addWidget(gridWidget);
    mainLayout->addWidget(shipsWidget);
    mainLayout->addWidget(rbapb);

    this->setLayout(mainLayout);
    this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                         stop : 0 #3EADCF, stop: 1 #ABE9CD);");

    connectFieldButtons();
    connectButtons();
}

void PreparationGameWidget::connectButtons() {
    //
    // Connect radioButtons with orientation
    //
    QObject::connect(rbapb->getVertical(), SIGNAL(clicked()),
                     this, SLOT(slotRadioButtonClicked()));
    QObject::connect(rbapb->getHorizantal(), SIGNAL(clicked()),
                     this, SLOT(slotRadioButtonClicked()));

    //
    // Connect button start
    //
    QObject::connect(shipsWidget, SIGNAL(signalShowStartGame()),
                     this, SLOT(slotActivateStartButton()));
    QObject::connect(shipsWidget, SIGNAL(signalHideStartGame()),
                     this, SLOT(slotDiactivateStartButton()));
    QObject::connect(rbapb->getAutoPlacementShips(), SIGNAL(clicked()),
                     this, SLOT(slotAutoPlacementShipsClicked()));

    //
    // Connect player with grid widget
    //
    QObject::connect(player1, &Player::signalDeleteShipFromFields,
                     gridWidget, &GridWidget::slotSetFieldsOnShipPosition);
    QObject::connect(this, &PreparationGameWidget::signalSetNullsShipsAndWidget,
                     shipsWidget, &ShipsWidget::slotSetNulls);
    QObject::connect(this, &PreparationGameWidget::signalSetMaxShipsAndWidget,
                     shipsWidget, &ShipsWidget::slotSetMax);
}

void PreparationGameWidget::slotAutoPlacementShipsClicked() {
    //
    // Проверка расставлены ли все корабли
    //
    if ((player1->getShipCount(1) + player1->getShipCount(2) + player1->getShipCount(3) + player1->getShipCount(4)) == 10) {
        player1->deleteAllShips();
        emit signalSetMaxShipsAndWidget();
    }
    AutomaticShipsPlacement::setRandomPositionShips(player1, gridWidget, shipsWidget);
    emit signalSetNullsShipsAndWidget();
}

void PreparationGameWidget::slotStartGameClicked() {
    Button **button = gridWidget->getField();

    for(size_t i = 0; i < gridWidget->getFieldCount(); ++i)
        QObject::disconnect(button[i], SIGNAL(signalClicked()),
                         this, SLOT(slotFieldClicked()));

    BattleGameWidget *bgw = new BattleGameWidget(player1, player1->getField());
    bgw->show();

    deleteLater();
}

void PreparationGameWidget::slotDiactivateStartButton() {
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
                     this, SLOT(slotStartGameClicked()));
}

void PreparationGameWidget::slotActivateStartButton() {
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
                     this, SLOT(slotStartGameClicked()));
}

void PreparationGameWidget::slotRadioButtonClicked() {
   if (rbapb->getVertical() == sender()) {
       orientation = false;
   }
   else if (rbapb->getHorizantal() == sender()) {
       orientation = true;
   }
}

void PreparationGameWidget::connectFieldButtons() {
    Button **button = gridWidget->getField();
    for(size_t i = 0; i < fieldsCount; ++i)
        QObject::connect(button[i], SIGNAL(signalClicked()),
                         this, SLOT(slotFieldClicked()));
}

void PreparationGameWidget::slotFieldClicked() {
    int number = gridWidget->findFieldNumber((Button*)sender());
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;

    QCursor *current_global_cursor = QApplication::overrideCursor();
    if (current_global_cursor != 0 && *(current_global_cursor) == Qt::ClosedHandCursor)
    {
        QVector<QPair<int, int>> coordinates =
                player1->convertPointAndOrientation2Coordinates(position, shipsWidget->getClickedShipType(), orientation);
        if (player1->canSetShipOnPosition(coordinates, orientation))
        {
            player1->setShipOnPosition(coordinates, shipsWidget->getClickedShipType(), orientation);
            gridWidget->setShipPositionInGrid(position, orientation, shipsWidget->getClickedShipType());
            shipsWidget->changeDigitPixMap();
            QApplication::restoreOverrideCursor();
            cursor() = Qt::ArrowCursor;
        }
    }
    else if (current_global_cursor == nullptr && cursor() == Qt::ArrowCursor && player1->hasShipOnPoint(position))
    {
        Ship *ship = player1->findShipByPosition(position);
        if (ship != nullptr) {
            shipsWidget->setChooseShip(player1->findShipByPosition(position)->getTypeOfShip());
            gridWidget->slotSetFieldsOnShipPosition(player1->convertPointAndOrientation2Coordinates(ship->getShipBegin(),
                                                         shipsWidget->getClickedShipType(), ship->getOrientationOfShip()),
                                                         ship->getOrientationOfShip());
            player1->deleteShipFromPosition(position);
            shipsWidget->returnChangedDigitPixMap();
            QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        }
    }
}

PreparationGameWidget::~PreparationGameWidget() {

}
