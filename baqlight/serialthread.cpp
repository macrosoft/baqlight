#include "serialthread.h"
#include "constants.h"
#include <QSerialPortInfo>
#include <QElapsedTimer>
#include <QDebug>

SerialThread::SerialThread(Screen *s, QObject *parent) : QThread(parent), screen(s) {
    serial.setPortName("/dev/ttyS0"); //change!
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.moveToThread(this);
    stop = false;
    startTimer(250, Qt::CoarseTimer);
}

void SerialThread::run() {
    QByteArray data;
    QElapsedTimer timer;
    timer.start();
    while (1) {
        if (stop || !serial.isOpen())
            break;
        mutex.lock();
        screen->capture();
        data.clear();
        data.append("baqlt", 5);
        for (int i = 0; i < PIXEL_COUNT; i++) {
            QColor color = screen->getPixel(i)->getColor();
            data.append(quint8(color.red()));
            data.append(quint8(color.green()));
            data.append(quint8(color.blue()));
        }
        serial.write(data);
        serial.waitForBytesWritten(1000);
        //qDebug() << "time: " << timer.elapsed();
    }
}

void SerialThread::pauseOrResume() {
    if (isRunning()) {
        stop = true;
    } else {
        stop = false;
        start();
    }
}

void SerialThread::timerEvent(QTimerEvent *) {
    mutex.unlock();
}
