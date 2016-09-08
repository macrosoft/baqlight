#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>
#include "serialthread.h"

class SystemTrayIcon : public QSystemTrayIcon {
    Q_OBJECT
public:
    explicit SystemTrayIcon(SerialThread *t, QObject *parent = 0);
public slots:
    void onOpenMenu();
signals:
    void openSettings();
private:
    SerialThread *thread;
    QMenu menu;
    QAction *pauseOrResumeAction;
};

#endif // SYSTEMTRAYICON_H
