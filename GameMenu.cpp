#include "GameMenu.h"
#include <QDebug>

GameMenu::GameMenu(const QString & result_information, QWidget *parent) :
    QWidget(parent),
    resultLabel(new QLabel(result_information, this)),
    exitButton(new QPushButton("Exit to main menu", this)),
    retryGameButton(new QPushButton("Retry", this)),
    continueGameButton(new QPushButton("Continue")),
    mainLayout(new QVBoxLayout(this))
{
    resultLabel->setAttribute(Qt::WA_TranslucentBackground);
    exitButton->setAttribute(Qt::WA_TranslucentBackground);
    retryGameButton->setAttribute(Qt::WA_TranslucentBackground);

    mainLayout->addWidget(resultLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(retryGameButton);
    mainLayout->addWidget(exitButton);
    if (result_information == "Game Pause") {
        continueGameButton->setParent(this);
        mainLayout->addWidget(continueGameButton);
    }

    setLayout(mainLayout);
    setResultMenuStyle(result_information);
    setWindowFlag(Qt::WindowStaysOnTopHint);

    QObject::connect(continueGameButton, SIGNAL(clicked()),
                     this, SLOT(slotContinueClicked()));
}


QPushButton*& GameMenu::getButtonExit() { return exitButton; }

QPushButton*& GameMenu::getButtonRetryGame() { return retryGameButton; }

void GameMenu::slotContinueClicked() { hide();}

void GameMenu::setResultMenuStyle(const QString & result_information) {
    QString qss_code;
    resultLabel->setStyleSheet("color : black;"
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

        continueGameButton->setStyleSheet(qss_code);
        this->setStyleSheet("background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
            stop : 0 #72A0C1	, stop: 1 #6391B2);");
    }
    exitButton->setStyleSheet(qss_code);
    retryGameButton->setStyleSheet(qss_code);
}

GameMenu::~GameMenu()
{

}
