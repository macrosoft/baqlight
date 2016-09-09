#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QSerialPort>
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
    QSerialPort serial;
    bool stop;
};

#endif // SERIALTHREAD_H
