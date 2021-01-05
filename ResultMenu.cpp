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
}


QPushButton*& ResultMenu::getButtonExit() { return button_exit; }
QPushButton*& ResultMenu::getButtonRetryGame() { return button_retry_game; }


