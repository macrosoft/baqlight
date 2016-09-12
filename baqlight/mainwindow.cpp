#include "mainwindow.h"
#include "constants.h"
#include "rgbledpixel.h"
#include "settingsfactory.h"

MainWindow::MainWindow(Screen *s, QWidget *parent)
    : QWidget(parent), screen(s) {
    setMinimumSize(640, 480);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    layout->addWidget(&picLabel, 10);
    QVBoxLayout *sidebar = new QVBoxLayout();
    layout->addLayout(sidebar);
    QPushButton *updateButton = new QPushButton(tr("Update"));
    sidebar->addWidget(updateButton);
    connect(updateButton, SIGNAL(clicked(bool)), SLOT(delayedScrenshot()));
    sidebar->addStretch();
    QPushButton *saveButton = new QPushButton(tr("Save"));
    sidebar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked(bool)), SLOT(save()));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    sidebar->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked(bool)), SLOT(close()));
}

MainWindow::~MainWindow() {

}

void MainWindow::delayedScrenshot() {
    QTimer::singleShot(10000, this, SLOT(updatePicture()));
}

void MainWindow::updatePicture() {
    screen->capture();
    screenshot = screen->getShot();
    QPainter painter(&screenshot);
    for (int i = 0; i < PIXEL_COUNT; i++) {
        const RgbLedPixel *pixel = screen->getPixel(i);
        painter.setBrush(pixel->getColor());
        painter.setPen(pixel->getColor());
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
        painter.drawRect(r);
    }
    picLabel.setPixmap(screenshot.scaled(picLabel.size(), Qt::KeepAspectRatio));
}

void MainWindow::load() {
    QVariantMap *settings = SettingsFactory::getSettings();
}

void MainWindow::showEvent(QShowEvent *) {
    load();
    updatePicture();
}

void MainWindow::resizeEvent(QResizeEvent *) {
    if (screenshot.isNull())
        return;
    picLabel.setPixmap(screenshot.scaled(picLabel.size(), Qt::KeepAspectRatio));
}

void MainWindow::save() {
    SettingsFactory::saveSettings();
}
