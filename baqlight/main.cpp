#include "mainwindow.h"
#include "serialthread.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialThread thread;
    thread.start();
    MainWindow w;
    w.show();

    return a.exec();
}
