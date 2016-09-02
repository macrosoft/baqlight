#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "screen.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QLabel picLabel;
    Screen *screen;
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
