#include "GameMenu.h"
#include <QDebug>

GameMenu::GameMenu(const QString & result_information, QWidget *parent) :
    QWidget(parent),
    label_result(new QLabel(result_information, this)),
    button_exit(new QPushButton("Exit to main menu", this)),
    button_retry_game(new QPushButton("Retry", this)),
    continue_game(new QPushButton("Continue")),
    vertical_layout(new QVBoxLayout(this))
{
    label_result->setAttribute(Qt::WA_TranslucentBackground);
    button_exit->setAttribute(Qt::WA_TranslucentBackground);
    button_retry_game->setAttribute(Qt::WA_TranslucentBackground);

//    button_exit->setFlat(true);
//    button_retry_game->setFlat(true)

    vertical_layout->addWidget(label_result, 0, Qt::AlignCenter);
    vertical_layout->addWidget(button_retry_game);
    vertical_layout->addWidget(button_exit);
    if (result_information == "Game Pause") {
        continue_game->setParent(this);
        vertical_layout->addWidget(continue_game);
    }

    setLayout(vertical_layout);
    //setFixedSize(200, 100);
    setResultMenuStyle(result_information);
    setWindowFlag(Qt::WindowStaysOnTopHint);

    QObject::connect(continue_game, SIGNAL(clicked()),
                     this, SLOT(continueClicked()));
}


QPushButton*& GameMenu::getButtonExit() { return button_exit; }
QPushButton*& GameMenu::getButtonRetryGame() { return button_retry_game; }
void GameMenu::continueClicked() { hide();}

void GameMenu::setResultMenuStyle(const QString & result_information) {
    QString qss_code;
    label_result->setStyleSheet("color : black;"
                                "background: transparent;"
                                "font-family: New Century Schoolbook;"
                                "font-size : 20px;");
    if (result_information == "Lose!") {
        qss_code = "QPushButton {\
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
                     }";

        this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                             stop : 0 #E65758, stop: 1 #771D32);");
    }
    else if (result_information == "Win!"){
        qss_code = "QPushButton {\
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
                    }";

        this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                             stop : 0 #50D5B7, stop: 1 #067D68);");
    }
    else {
        qss_code = "QPushButton {\
                         color : black;\
                         background: transparent;\
                         font-family: New Century Schoolbook;\
                         font-size : 20px;\
                         border-radius: 1px;\
                         }\
                         QPushButton:hover {\
                         background-color :  blue;\
                         }\
                         QPushButton:pressed {\
                         background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                         stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                         }";

        continue_game->setStyleSheet(qss_code);
        this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
            stop : 0 #72A0C1	, stop: 1 #6391B2);");
    }
    button_exit->setStyleSheet(qss_code);
    button_retry_game->setStyleSheet(qss_code);
}

GameMenu::~GameMenu()
{

}
