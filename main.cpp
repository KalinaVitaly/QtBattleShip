#include "MainMenu.h"
#include "GridWidget.h"
#include "ShipsWidget.h"
#include "RadioButtonsAndPushButtons.h"
#include "BattleGameWidget.h"
#include <QApplication>
#include "AutomaticShipsPlacement.h"
#include "Player.h"
#include <QSpinBox>
#include "GridLabelWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Player player;
//    AutomaticShipsPlacement::setRandomPositionShips(&player);
    MainWindow w;
//    int arr[10][10];
//    for (int i = 0; i < 10; ++i) {
//        for (int j = 0; j < 10; ++j) {
//            arr[i][j] = rand() % 2;
//        }
//    }
//    GridLabelWidget k(arr, QSize(40, 40));
    //GridWidget w;
    //ShipsWidget w;
    //RadioButtonsAndPushButtons w1;
    w.show();
//    w1.show();
    return a.exec();
}
