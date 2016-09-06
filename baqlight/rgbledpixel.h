#ifndef RGBLEDPIXEL_H
#define RGBLEDPIXEL_H

#include <QtCore>
#include <QColor>

class RgbLedPixel : public QObject {
    Q_OBJECT
public:
    explicit RgbLedPixel(QObject *parent = 0);
    QColor getColor() const;
    void setColor(const QColor &value);
    QRect getRect() const;
    void setRect(const QRect &value);
    Qt::AlignmentFlag getAlignment() const;
    void setAlignment(const Qt::AlignmentFlag &value);

private:
    QColor color;
    QRect rect;
    Qt::AlignmentFlag alignment;
};

#endif // RGBLEDPIXEL_H
