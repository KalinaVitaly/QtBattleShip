#include "MainMenu.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
//    ResultMenu w("Lose!");
    w.show();
//    w1.show();
    return a.exec();
}
