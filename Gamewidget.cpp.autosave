#include "Gamewidget.h"
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

void GameWidget::connectFielButtondWithFieldClicked()
{
    QPushButton **button = grid_widget->getField();
    for(size_t i = 0; i < grid_widget->getFieldCount(); ++i)
        QObject::connect(button[i], SIGNAL(clicked()),
                         this, SLOT(fieldClicked()));
}

void GameWidget::fieldClicked()
{
    if (*(QApplication::overrideCursor()) == Qt::ClosedHandCursor)
    {
        bool orientation = true;
        int number = grid_widget->findFieldNumber((QPushButton*)sender());
        QPair<int, int> position;
        position.first = number % 10;
        position.second = number / 10;
        qDebug() << position.first << " " << position.second;
        qDebug() << ships_and_digits->getClickedShipType();

        if (player1.canSetShipInThisPosition(ships_and_digits->getClickedShipType(), position, orientation))
        {
            player1.setShipPosition(ships_and_digits->getClickedShipType(), position, orientation);
            grid_widget->setShipPositionInGrid(position, orientation, ships_and_digits->getClickedShipType());
            QApplication::setOverrideCursor(Qt::ArrowCursor);
        }
    }
}
