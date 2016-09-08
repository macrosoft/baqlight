#include "systemtrayicon.h"
#include <QApplication>

SystemTrayIcon::SystemTrayIcon(SerialThread *t, QObject *parent) : thread(t), QSystemTrayIcon(parent) {
    setIcon(QIcon(":/res/icon.png"));
    connect(&menu, SIGNAL(aboutToShow()), SLOT(onOpenMenu()));
    QAction *action;
    action = menu.addAction(QObject::tr("&Settings..."));
    connect(action, SIGNAL(triggered(bool)), SIGNAL(openSettings()));
    pauseOrResumeAction = menu.addAction(QObject::tr("&Pause"));
    connect(pauseOrResumeAction, SIGNAL(triggered(bool)), thread, SLOT(pauseOrResume()));
    action = menu.addAction(QObject::tr("&Quit"));
    connect(action, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    setContextMenu(&menu);
}

void SystemTrayIcon::onOpenMenu() {
    if (thread->isRunning()) {
        pauseOrResumeAction->setText("&Pause");
    } else {
        pauseOrResumeAction->setText("&Resume");
    }
}
