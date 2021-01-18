  #include "MainMenu.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    QFont font("times", 60);
    QSize size(300, 60);
    layout = new QVBoxLayout;
    //QImage("/home/vitaly/QtProject/WorkWithPictures/BattleShips.jpg").scaled(1800, 900).save("/home/vitaly/QtProject/WorkWithPictures/BattleShips.jpg");
    background_ships = new QPixmap("/home/vitaly/QtProject/BattleShips/images/field/BattleShips.jpg");
    game_name = new QLabel("BattleShips", this);
    game_name->setFont(font);
    palette.setBrush(this->backgroundRole(), *background_ships);

    layout->addWidget(game_name, 0, Qt::AlignCenter);
    setButtons(start_game, size, "Start game");
    setButtons(settings, size, "Settings");
    setButtons(exit, size, "Exit");

    QObject::connect(start_game, SIGNAL(clicked()),
                     this, SLOT(startGameClicked()));
    QObject::connect(settings, SIGNAL(clicked()),
                     this, SLOT(settingsClicked()));
    QObject::connect(exit, SIGNAL(clicked()),
                     this, SLOT(exitClicked()));


    this->setFixedSize(1800, 900);
    this->setPalette(palette);
    this->setLayout(layout);
}

void MainWindow::setButtons(QPushButton *&button, const QSize &size, const QString &str)
{
    button = new QPushButton(str, this);
    button->setStyleSheet("QPushButton {\
                           color : black;\
                           background-color : rgba(0, 250, 250, 200);\
                           font-family: New Century Schoolbook;\
                           font-size : 25px;\
                           border-radius: 10px;\
                           }\
                           QPushButton:pressed {\
                           background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                           stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                           }");
    button->setFixedSize(size);
    layout->addWidget(button, 0, Qt::AlignCenter);
}

void MainWindow::startGameClicked()
{
    PreparationGameWidget *wgame = new PreparationGameWidget;
    wgame->show();
    this->hide();
}

void MainWindow::exitClicked()
{
    this->hide();
}

void MainWindow::settingsClicked()
{
    //add settings=)
}

MainWindow::~MainWindow() {
    delete layout;
    delete game_name;
    delete start_game;
    delete settings;
    delete exit;
}




