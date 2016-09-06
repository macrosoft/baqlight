#include "screen.h"
#include "constants.h"
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
    for (int dx = x + AVG_COLOR_STEP/2; dx < width; dx += AVG_COLOR_STEP) {
        for (int dy = y + AVG_COLOR_STEP/2; dy < height; dy += AVG_COLOR_STEP) {
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
    count = qMax(count, quint64(w*h*0.1/AVG_COLOR_STEP/AVG_COLOR_STEP));
    color.setRed(r/count);
    color.setGreen(g/count);
    color.setBlue(b/count);
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
