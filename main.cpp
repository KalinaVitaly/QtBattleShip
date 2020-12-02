#include "MainMenu.h"
#include "GridWidget.h"
#include "ShipsWidget.h"
#include "RadioButtonsAndPushButtons.h"
#include "BattleGameWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //GridWidget w;
    //ShipsWidget w;
    //RadioButtonsAndPushButtons w1;
    w.show();
    //w1.show();
    return a.exec();
}
