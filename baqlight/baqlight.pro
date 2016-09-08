QT       += core gui widgets serialport

TARGET = baqlight
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    screen.cpp \
    rgbledpixel.cpp \
    serialthread.cpp

HEADERS  += mainwindow.h \
    screen.h \
    constants.h \
    rgbledpixel.h \
    serialthread.h

RESOURCES += \
    res.qrc
