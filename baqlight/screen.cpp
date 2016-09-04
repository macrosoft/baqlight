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
    int width = x + w;
    int height = y + h;
    for (int dx = x; dx < width; ++dx) {
        for (int dy = y; dy < height; ++dy) {
            QColor pixel(screenshot.pixel(dx, dy));
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
    qreal saturation = qMin(1.0, color.hsvSaturationF()*1.5);
    color.setHsvF(color.hsvHueF(), saturation, color.valueF());
    int lightness = (color.red() + color.green() + color.blue())/3;
    if (lightness < 64) {
        int diff = (64 - lightness)/3;
        color.setRgb(color.red() + diff, color.green() + diff, color.blue() + diff);
    }
    return color;
}

void Screen::capture() {
    QScreen *screen = QGuiApplication::primaryScreen();
    screenshot = screen->grabWindow(0).toImage();
}
