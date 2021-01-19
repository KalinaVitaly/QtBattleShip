#include "MainMenu.h"
#include "GridButtonWidget.h"
#include "ShipsWidget.h"
#include "RadioButtonsAndPushButtons.h"
#include "BattleGameWidget.h"
#include <QApplication>
#include "AutomaticShipsPlacement.h"
#include "Player.h"
#include <QSpinBox>
#include "GridLabelWidget.h"
#include "ResultMenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
//    ResultMenu w("Lose!");
    w.show();
//    w1.show();
    return a.exec();
}
