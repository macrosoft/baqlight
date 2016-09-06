#include "mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    QPushButton *updateButton = new QPushButton("update");
    layout->addWidget(updateButton);
    connect(updateButton, SIGNAL(clicked(bool)), SLOT(delayedScrenshot()));
    layout->addWidget(&picLabel);
    screen = new Screen(this);
    screen->capture();
    updatePicture();
}

MainWindow::~MainWindow() {

}

void MainWindow::delayedScrenshot() {
    QTimer::singleShot(10000, this, SLOT(updatePicture()));
}

void MainWindow::updatePicture() {
    screen->capture();
    QPixmap screenshot = screen->getShot();
    QPainter *painter = new QPainter(&screenshot);
    for (int i = 6; i >= 0; --i) {
        int y = SCREEN_HEIGHT - 105;
        int x = 105*i;
        QColor avgColor = screen->getAvgColor(x, y, 105, 105);
        painter->setBrush(avgColor);
        painter->setPen(avgColor);
        painter->drawRect(x, SCREEN_HEIGHT - 20, 105, 20);
    }
    for (int i = 9; i >= 0; --i) {
        int y = 105*i;
        int x = 0;
        QColor avgColor = screen->getAvgColor(x, y, 105, 105);
        painter->setBrush(avgColor);
        painter->setPen(avgColor);
        painter->drawRect(x, y, 20, 105);
    }
    for (int i = 0; i < 16; i++) {
        int y = 0;
        int x = 105*i;
        QColor avgColor = screen->getAvgColor(x, y, 105, 105);
        painter->setBrush(avgColor);
        painter->setPen(avgColor);
        painter->drawRect(x, y, 105, 20);
    }
    for (int i = 0; i < 10; ++i) {
        int y = 105*i;
        int x = SCREEN_WIDTH - 105;
        QColor avgColor = screen->getAvgColor(x, y, 105, 105);
        painter->setBrush(avgColor);
        painter->setPen(avgColor);
        painter->drawRect(SCREEN_WIDTH - 20, y, 20, 105);
    }
    for (int i = 0; i < 7; i++) {
        int y = SCREEN_HEIGHT - 105;
        int x = 105*(i+9);
        QColor avgColor = screen->getAvgColor(x, y, 105, 105);
        painter->setBrush(avgColor);
        painter->setPen(avgColor);
        painter->drawRect(x, SCREEN_HEIGHT - 20, 105, 20);
    }
    picLabel.setPixmap(screenshot.scaled(picLabel.size(), Qt::KeepAspectRatio));
}


void MainWindow::resizeEvent(QResizeEvent *) {
    //updatePicture();
}
