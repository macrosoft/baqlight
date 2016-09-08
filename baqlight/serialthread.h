#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QSerialPort>
#include <QMutex>

class SerialThread : public QThread {
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = 0);
    void run();
public slots:
    void pauseOrResume();
private:
    QSerialPort serial;
    bool stop;
};

#endif // SERIALTHREAD_H
