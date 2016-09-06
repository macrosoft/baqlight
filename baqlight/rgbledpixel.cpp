#include "rgbledpixel.h"

RgbLedPixel::RgbLedPixel(QObject *parent) : QObject(parent) {
    color = Qt::black;
    alignment = Qt::AlignCenter;
}

QColor RgbLedPixel::getColor() const {
    return color;
}

void RgbLedPixel::setColor(const QColor &value) {
    color = value;
}

QRect RgbLedPixel::getRect() const {
    return rect;
}

void RgbLedPixel::setRect(const QRect &value){
    rect = value;
}

Qt::AlignmentFlag RgbLedPixel::getAlignment() const {
    return alignment;
}

void RgbLedPixel::setAlignment(const Qt::AlignmentFlag &value) {
    alignment = value;
}

