  #include "MainMenu.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    backgroundShipPixmap(new QPixmap("/home/vitaly/QtProject/BattleShips/images/field/BattleShips.jpg")),
    gameNameLabel(new QLabel("BattleShips", this)),
    mainLayout(new QVBoxLayout(this))
{
    QPalette palette;
    QFont font("times", 60);
    QSize size(300, 60);

    gameNameLabel->setFont(font);
    palette.setBrush(this->backgroundRole(), *backgroundShipPixmap);

    mainLayout->addWidget(gameNameLabel, 0, Qt::AlignCenter);
    setButtons(startGameButton, size, "Start game");
    setButtons(settingsButton, size, "Settings");
    setButtons(exitButton, size, "Exit");

    QObject::connect(startGameButton, SIGNAL(clicked()),
                     this, SLOT(slotStartGameClicked()));
    QObject::connect(settingsButton, SIGNAL(clicked()),
                     this, SLOT(slotSettingsClicked()));
    QObject::connect(exitButton, SIGNAL(clicked()),
                     this, SLOT(slotExitClicked()));

    this->setFixedSize(1800, 900);
    this->setPalette(palette);
    this->setLayout(mainLayout);
}

//QPixmap *backgroundShipPixmap;


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
                           QPushButton:hover {\
                           background-color :   rgb(224, 255, 50);\
                           }\
                           QPushButton:pressed {\
                           background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,\
                           stop : 0 rgba(8, 38, 103, 200), stop: 1 rgba(16, 71, 19, 200));\
                           }");
    button->setFixedSize(size);
    mainLayout->addWidget(button, 0, Qt::AlignCenter);
}

void MainWindow::slotStartGameClicked()
{
    PreparationGameWidget *preparationGameWidget = new PreparationGameWidget;
    preparationGameWidget->show();

    close();
}

void MainWindow::slotExitClicked()
{
    close();
}

void MainWindow::slotSettingsClicked()
{
    //add settings=)
}

MainWindow::~MainWindow()
{
    delete backgroundShipPixmap;
}




