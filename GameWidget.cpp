#include "GameWidget.h"
#include <QDebug>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    fields_count(100)
{
    //grid widget 880*880
    this->setFixedSize(1800, 1000);
    horizantal_layout = new QHBoxLayout;
    vertical_layout = new QVBoxLayout;

    grid_widget = new GridWidget;
    ships_and_digits = new ShipsWidget;

    horizantal_layout->addWidget(grid_widget);
    horizantal_layout->addWidget(ships_and_digits);

    this->setLayout(horizantal_layout);

    connectFielButtondWithFieldClicked();
}

void GameWidget::connectFielButtondWithFieldClicked() {
    QPushButton **button = grid_widget->getField();
    for(size_t i = 0; i < grid_widget->getFieldCount(); ++i)
        QObject::connect(button[i], SIGNAL(clicked()),
                         this, SLOT(fieldClicked()));
}

void GameWidget::fieldClicked() {
    int number = grid_widget->findFieldNumber((QPushButton*)sender());
    QPair<int, int> position;
    position.first = number % 10;
    position.second = number / 10;
    bool orientation = 1;

    QCursor *current_global_cursor = (QApplication::overrideCursor());
    if (current_global_cursor != 0 && *(QApplication::overrideCursor()) == Qt::ClosedHandCursor)
    {
        QVector<QPair<int, int>> coordinates = player1.convertPointAndOrientation2Coordinates(position, ships_and_digits->getClickedShipType(), orientation);
        if (player1.canSetShipOnPosition(coordinates))
        {
            player1.setShipOnPosition(coordinates, ships_and_digits->getClickedShipType(), orientation);
            grid_widget->setShipPositionInGrid(position, orientation, ships_and_digits->getClickedShipType());
            ships_and_digits->changeDigitPixMap();
            QApplication::restoreOverrideCursor();
        }
    }
    else if ((current_global_cursor == 0) && (cursor() == Qt::ArrowCursor) && player1.hasShipOnPoint(position))
    {
        qDebug() << "here";
        Ship *ship = player1.findShipByPosition(position);
        if (ship != nullptr) {
            ships_and_digits->setChooseShip(player1.findShipByPosition(position)->getShipType());
            grid_widget->setFieldPixOnShipPositionInGrid(player1.convertPointAndOrientation2Coordinates(ship->getShipbegin(), ships_and_digits->getClickedShipType(), orientation),
                                                         ship->getOrientation());
            player1.deleteShipFromPosition(position);
            ships_and_digits->returnChangedDigitPixMap();
            QApplication::setOverrideCursor(Qt::ClosedHandCursor);
        }
    }
}
