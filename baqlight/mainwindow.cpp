#include "mainwindow.h"
#include "constants.h"
#include "rgbledpixel.h"

MainWindow::MainWindow(Screen *s, QWidget *parent)
    : QWidget(parent), screen(s) {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    QPushButton *updateButton = new QPushButton("update");
    layout->addWidget(updateButton);
    connect(updateButton, SIGNAL(clicked(bool)), SLOT(delayedScrenshot()));
    layout->addWidget(&picLabel);
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
    for (int i = 0; i < PIXEL_COUNT; i++) {
        const RgbLedPixel *pixel = screen->getPixel(i);
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
