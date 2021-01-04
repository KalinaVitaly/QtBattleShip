#include "ResultMenu.h"
#include <QDebug>

ResultMenu::ResultMenu(const QString & result_information, QWidget *parent) : QWidget(parent)
{
    label_result = new QLabel(QString("You ") + result_information);
    button_exit = new QPushButton("Exit to main menu");
    button_retry_game = new QPushButton("Retry");
    vertical_layout = new QVBoxLayout;

    vertical_layout->addWidget(label_result, 0, Qt::AlignCenter);
    vertical_layout->addWidget(button_retry_game);
    vertical_layout->addWidget(button_exit);

    setLayout(vertical_layout);
    setFixedSize(200, 100);

    connectButtons();
}

void ResultMenu::connectButtons() {
    QObject::connect(button_exit, SIGNAL(clicked()),
                     this, SLOT(exitButtonClicked()));
    QObject::connect(button_retry_game, SIGNAL(clicked()),
                     this, SLOT(retryButtonClicked()));
}

void ResultMenu::exitButtonClicked() {
    qDebug() << "Exit Button Clicked";
    //Add hide
}

void ResultMenu::retryButtonClicked() {
    qDebug() << "Retry Button Clicked";
}
