#include "mainwindow.h"
#include "serialthread.h"
#include <QApplication>
#include <QSystemTrayIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSystemTrayIcon trayIcon;
    trayIcon.setIcon(QIcon(":/res/icon.png"));
    trayIcon.show();
    SerialThread thread;
    thread.start();
    MainWindow w;
    w.show();

    return a.exec();
}
