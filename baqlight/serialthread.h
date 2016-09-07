#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QSerialPort>

class SerialThread : public QThread {
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = 0);
    void run();
private:
    QSerialPort serial;
};

#endif // SERIALTHREAD_H
