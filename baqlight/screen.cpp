#include "screen.h"
#include "constants.h"
#include <QGuiApplication>
#include <QScreen>

Screen::Screen(QObject *parent) : QObject(parent) {
    minCount = PIXEL_SIZE*PIXEL_SIZE*0.2/AVG_COLOR_STEP/AVG_COLOR_STEP;
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
}

QPixmap Screen::getShot() {
    return QPixmap::fromImage(screenshot);
}

void Screen::capture() {
    QScreen *screen = QGuiApplication::primaryScreen();
    screenshot = screen->grabWindow(0).toImage();
    foreach (RgbLedPixel *pixel, pixels) {
        updatePixelColor(pixel);
    }
}

const RgbLedPixel *Screen::getPixel(const int i) {
    return pixels[i];
}

void Screen::updatePixelColor(RgbLedPixel *pixel) {
    quint64 r = 0;
    quint64 g = 0;
    quint64 b = 0;
    quint64 count = 0;
    QRect rect = pixel->getRect();
    int width = rect.left() + rect.width();
    int height = rect.top() + rect.height();
    for (int dx = rect.left() + AVG_COLOR_STEP/2; dx < width; dx += AVG_COLOR_STEP) {
        for (int dy = rect.top() + AVG_COLOR_STEP/2; dy < height; dy += AVG_COLOR_STEP) {
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
    count = qMax(count, minCount);
    color.setRed(r/count);
    color.setGreen(g/count);
    color.setBlue(b/count);
    int lightness = (color.red() + color.green() + color.blue())/3;
    if (lightness < 64) {
        int diff = (64 - lightness)/3;
        color.setRgb(color.red() + diff, color.green() + diff, color.blue() + diff);
    }
    pixel->setColor(color);
}
