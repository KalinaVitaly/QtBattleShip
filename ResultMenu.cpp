#include "ResultMenu.h"
#include <QDebug>

ResultMenu::ResultMenu(const QString & result_information, QWidget *parent) : QWidget(parent)
{
    label_result = new QLabel(QString("You ") + result_information);
    button_exit = new QPushButton("Exit to main menu");
    button_retry_game = new QPushButton("Retry");
    vertical_layout = new QVBoxLayout;

    label_result->setAttribute(Qt::WA_TranslucentBackground);
    button_exit->setAttribute(Qt::WA_TranslucentBackground);
    button_retry_game->setAttribute(Qt::WA_TranslucentBackground);

//    button_exit->setFlat(true);
//    button_retry_game->setFlat(true)

    vertical_layout->addWidget(label_result, 0, Qt::AlignCenter);
    vertical_layout->addWidget(button_retry_game);
    vertical_layout->addWidget(button_exit);

    setLayout(vertical_layout);
    setFixedSize(200, 100);
    setResultMenuStyle(result_information);
}


QPushButton*& ResultMenu::getButtonExit() { return button_exit; }
QPushButton*& ResultMenu::getButtonRetryGame() { return button_retry_game; }

void ResultMenu::setResultMenuStyle(const QString & result_information) {
    label_result->setStyleSheet("color : black;"
                                "background: transparent;"
                                "font-family: New Century Schoolbook;"
                                "font-size : 20px;");
    if (result_information == "Lose!") {
        button_exit->setStyleSheet("QPushButton {\
                                   color : black;\
                                   background: transparent;\
                                   font-family: New Century Schoolbook;\
                                   font-size : 20px;\
                                   border-radius: 1px;\
                                   }\
                                   QPushButton:hover {\
                                   background-color : #808080;\
                                   }\
                                   QPushButton:pressed {\
                                   background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                                   stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                                   }");
        button_retry_game->setStyleSheet("QPushButton {\
                                         color : black;\
                                         background: transparent;\
                                         font-family: New Century Schoolbook;\
                                         font-size : 20px;\
                                         border-radius: 1px;\
                                         }\
                                         QPushButton:hover {\
                                         background-color :   #808080;\
                                         }\
                                         QPushButton:pressed {\
                                         background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                                         stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                                         }");
        this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                             stop : 0 #E65758, stop: 1 #771D32);");
    }
    else {
        button_exit->setStyleSheet("QPushButton {\
                                   color : black;\
                                   background: transparent;\
                                   font-family: New Century Schoolbook;\
                                   font-size : 20px;\
                                   border-radius: 1px;\
                                   }\
                                   QPushButton:hover {\
                                   background-color :  rgba(16, 71, 19, 50);\
                                   }\
                                   QPushButton:pressed {\
                                   background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                                   stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                                   }");
        button_retry_game->setStyleSheet("QPushButton {\
                                         color : black;\
                                         background: transparent;\
                                         font-family: New Century Schoolbook;\
                                         font-size : 20px;\
                                         border-radius: 1px;\
                                         }\
                                         QPushButton:hover {\
                                         background-color :  rgba(16, 71, 19, 50);\
                                         }\
                                         QPushButton:pressed {\
                                         background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                                         stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                                         }");
        this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                             stop : 0 #50D5B7, stop: 1 #067D68);");
    }
}

ResultMenu::~ResultMenu() {
    delete label_result;
    delete button_exit;
    delete button_retry_game;
    delete vertical_layout;
}
