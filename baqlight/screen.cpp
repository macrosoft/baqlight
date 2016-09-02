#include "screen.h"
#include <QGuiApplication>
#include <QScreen>

Screen::Screen(QObject *parent) : QObject(parent) {

}

QPixmap Screen::getShot() {
    return QPixmap::fromImage(screenshot);
}

QColor Screen::getAvgColor(int x, int y, int w, int h) {
    quint64 r = 0;
    quint64 g = 0;
    quint64 b = 0;
    quint64 count = 0;
    for (int dx = x; dx < w; ++dx) {
        for (int dy = y; dy < h; ++dy) {
            QColor pixel(screenshot.pixel(x + dx, y + dy));
            if (pixel.valueF() > 0.10) {
                count++;
                r += pixel.red();
                g += pixel.green();
                b += pixel.blue();
            }
        }
    }
    QColor color;
    count = qMax(count, quint64(w*h*0.1));
    color.setRed(r/count);
    color.setGreen(g/count);
    color.setBlue(b/count);
    qreal saturation = color.hsvSaturationF()*2.0;
    qreal value = qMax(0.25, color.valueF());
    color.setHsvF(color.hsvHueF(), saturation, value);
    return color;
}

void Screen::capture() {
    QScreen *screen = QGuiApplication::primaryScreen();
    screenshot = screen->grabWindow(0).toImage();
}
