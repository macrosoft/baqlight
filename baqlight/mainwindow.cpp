#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    QPushButton *updateButton = new QPushButton("update");
    layout->addWidget(updateButton);
    connect(updateButton, SIGNAL(clicked(bool)), SLOT(updatePicture()));
    layout->addWidget(&picLabel);
    screen = new Screen(this);
    screen->capture();
    updatePicture();
}

MainWindow::~MainWindow() {

}

void MainWindow::updatePicture() {
    screen->capture();
    QPixmap screenshot = screen->getShot();
    QColor avgColor = screen->getAvgColor(0, 0, 1680, 1050);
    QPainter *painter = new QPainter(&screenshot);
    painter->setBrush(avgColor);
    painter->setPen(avgColor);
    painter->drawRect(0, 0, 100, 100);
    picLabel.setPixmap(screenshot.scaled(picLabel.size(), Qt::KeepAspectRatio));
}


void MainWindow::resizeEvent(QResizeEvent *) {
    updatePicture();
}
