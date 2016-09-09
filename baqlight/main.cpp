#include "mainwindow.h"
#include "systemtrayicon.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Screen *screen = new Screen();
    SerialThread thread(screen);
    SystemTrayIcon trayIcon(&thread);
    trayIcon.show();
    MainWindow window(screen);
    thread.start();
    QObject::connect(&trayIcon, SIGNAL(openSettings()), &window, SLOT(show()));
    return a.exec();
}
