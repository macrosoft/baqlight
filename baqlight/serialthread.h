#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QSerialPort>
#include <QMutex>
#include "screen.h"

class SerialThread : public QThread {
    Q_OBJECT
public:
    explicit SerialThread(Screen *s, QObject *parent = 0);
    void run();
public slots:
    void pauseOrResume();
private:
    Screen *screen;
    QMutex mutex;
    QSerialPort serial;
    bool stop;

    void timerEvent(QTimerEvent *);
};

#endif // SERIALTHREAD_H
