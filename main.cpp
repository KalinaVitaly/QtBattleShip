#include "mainwindow.h"
#include "Gridwidget.h"
#include "ShipsWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //GridWidget w;
    //ShipsWidget w;
    w.show();
    return a.exec();
}
