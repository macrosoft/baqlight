#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "screen.h"
#include "rgbledpixel.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void delayedScrenshot();
    void updatePicture();
private:
    QLabel picLabel;
    Screen *screen;
    QVector<RgbLedPixel *> pixels;
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
