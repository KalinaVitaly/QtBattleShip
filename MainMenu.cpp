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
    font = {"times", 30};



    layout->addWidget(game_name, 0, Qt::AlignCenter);
    setButtons(start_game, font, size, "Start game");
    setButtons(settings, font, size, "Settings");
    setButtons(exit, font, size, "Exit");

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

void MainWindow::setButtons(QPushButton *&button, const QFont &font, const QSize &size, const QString &str)
{
    button = new QPushButton(str, this);
    button->setFont(font);
    button->setFixedSize(size);
    layout->addWidget(button, 0, Qt::AlignCenter);
}

void MainWindow::startGameClicked()
{
    GameWidget *wgame = new GameWidget;
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




