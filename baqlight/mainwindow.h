#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "screen.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(Screen *s, QWidget *parent = 0);
    ~MainWindow();
public slots:
    void delayedScrenshot();
    void updatePicture();
private:
    QLabel picLabel;
    Screen *screen;
    QPixmap screenshot;
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
