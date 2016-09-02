#ifndef SCREEN_H
#define SCREEN_H

#include <QColor>
#include <QImage>
#include <QPixmap>

class Screen : public QObject {
    Q_OBJECT
public:
    explicit Screen(QObject *parent = 0);
    QColor getAvgColor(int x, int y, int w, int h);
    QPixmap getShot();
    void capture();
private:
    QImage screenshot;
};

#endif // SCREEN_H
