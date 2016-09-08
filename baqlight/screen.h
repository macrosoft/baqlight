#ifndef SCREEN_H
#define SCREEN_H

#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QRect>
#include "rgbledpixel.h"

class Screen : public QObject {
    Q_OBJECT
public:
    explicit Screen(QObject *parent = 0);
    QPixmap getShot();
    void capture();
    const RgbLedPixel *getPixel(const int i);
private:
    QImage screenshot;
    quint64 minCount;
    QVector<RgbLedPixel *> pixels;
    void updatePixelColor(RgbLedPixel *pixel);
};

#endif // SCREEN_H
