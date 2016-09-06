#ifndef SCREEN_H
#define SCREEN_H

#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QRect>

class Screen : public QObject {
    Q_OBJECT
public:
    explicit Screen(QObject *parent = 0);
    QColor getAvgColor(const QRect rect);
    QPixmap getShot();
    void capture();
private:
    QImage screenshot;
    quint64 maxCount;
};

#endif // SCREEN_H
