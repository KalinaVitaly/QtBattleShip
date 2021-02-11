#include "MainMenu.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    try {
//        MainWindow w;
//        w.show();
//    } catch (std::exception & e) {
//        qDebug() << e.what();
//    }

    return a.exec();
}
