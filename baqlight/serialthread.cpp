#include "serialthread.h"
#include "constants.h"
#include <QSerialPortInfo>
#include <QElapsedTimer>
#include <QDebug>

SerialThread::SerialThread(QObject *parent) : QThread(parent) {
    serial.setPortName("/dev/ttyS0"); //change!
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.moveToThread(this);
    stop = false;
}

void SerialThread::run() {
    QByteArray data;
    data.resize(50*3 + 5);
    QElapsedTimer timer;
    timer.start();
    while (1) {
        if (stop)
            break;
        serial.write(data);
        serial.waitForBytesWritten(1000);
        qDebug() << "time: " << timer.elapsed();
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

