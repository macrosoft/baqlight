#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    layout->addWidget(&picLabel);
    screen = new Screen(this);
    screen->capture();
    QPixmap *screenshot = screen->getShot();
    picLabel.setPixmap(screenshot->scaled(picLabel.size(), Qt::KeepAspectRatio));
}

MainWindow::~MainWindow() {

}

void MainWindow::resizeEvent(QResizeEvent *) {
    QPixmap *screenshot = screen->getShot();
    picLabel.setPixmap(screenshot->scaled(picLabel.size(), Qt::KeepAspectRatio));
}
