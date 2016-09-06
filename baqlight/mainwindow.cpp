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
    for (int i = 6; i >= 0; --i) {
        RgbLedPixel *pixel = new RgbLedPixel();
        pixels.append(pixel);
        int x = PIXEL_SIZE*i;
        int y = SCREEN_HEIGHT - PIXEL_SIZE;
        pixel->setRect(QRect(x, y, PIXEL_SIZE, PIXEL_SIZE));
        pixel->setAlignment(Qt::AlignBottom);
    }
    for (int i = 9; i >= 0; --i) {
        RgbLedPixel *pixel = new RgbLedPixel();
        pixels.append(pixel);
        int x = 0;
        int y = PIXEL_SIZE*i;
        pixel->setRect(QRect(x, y, PIXEL_SIZE, PIXEL_SIZE));
        pixel->setAlignment(Qt::AlignLeft);
    }
    for (int i = 0; i < 16; i++) {
        RgbLedPixel *pixel = new RgbLedPixel();
        pixels.append(pixel);
        int x = PIXEL_SIZE*i;
        int y = 0;
        pixel->setRect(QRect(x, y, PIXEL_SIZE, PIXEL_SIZE));
        pixel->setAlignment(Qt::AlignTop);
    }
    for (int i = 0; i < 10; ++i) {
        RgbLedPixel *pixel = new RgbLedPixel();
        pixels.append(pixel);
        int x = SCREEN_WIDTH - PIXEL_SIZE;
        int y = PIXEL_SIZE*i;
        pixel->setRect(QRect(x, y, PIXEL_SIZE, PIXEL_SIZE));
        pixel->setAlignment(Qt::AlignRight);
    }
    for (int i = 0; i < 7; i++) {
        RgbLedPixel *pixel = new RgbLedPixel();
        pixels.append(pixel);
        int x = PIXEL_SIZE*(i + 9);
        int y = SCREEN_HEIGHT - PIXEL_SIZE;
        pixel->setRect(QRect(x, y, PIXEL_SIZE, PIXEL_SIZE));
        pixel->setAlignment(Qt::AlignBottom);
    }
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
    foreach (RgbLedPixel *pixel, pixels) {
        pixel->setColor(screen->getAvgColor(pixel->getRect()));
        painter->setBrush(pixel->getColor());
        painter->setPen(pixel->getColor());
        QRect r = pixel->getRect();
        switch (pixel->getAlignment()) {
        case Qt::AlignBottom:
            r.setTop(r.top() + PIXEL_SIZE - 20);
            r.setHeight(20);
            break;
        case Qt::AlignLeft:
            r.setWidth(20);
            break;
        case Qt::AlignTop:
            r.setHeight(20);
            break;
        case Qt::AlignRight:
            r.setLeft(r.left() + PIXEL_SIZE - 20);
            r.setWidth(20);
            break;
        default:
            break;
        }
        painter->drawRect(r);
    }
    picLabel.setPixmap(screenshot.scaled(picLabel.size(), Qt::KeepAspectRatio));
}


void MainWindow::resizeEvent(QResizeEvent *) {
    //updatePicture();
}
