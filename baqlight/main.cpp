#include "mainwindow.h"
#include "systemtrayicon.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    SerialThread thread;
    SystemTrayIcon trayIcon(&thread);
    trayIcon.show();
    MainWindow window;
    thread.start();
    QObject::connect(&trayIcon, SIGNAL(openSettings()), &window, SLOT(show()));
    return a.exec();
}
