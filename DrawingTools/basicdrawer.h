#ifndef DRAWER_H
#define DRAWER_H

#include <QPainterPath>
#include <QColor>
#include <QPixmap>

class BasicDrawer
{
public:


    static QPixmap warningIcon(QSize size, QColor foreground, QColor background);
    static QPixmap errorIcon(QSize size, QColor foreground, QColor background);

protected:
    BasicDrawer();
    static QPainterPath trianglePath(uint32_t width, uint32_t height, qreal percPadding, qreal percRoundCorner);
    static QPainterPath crossPath(uint32_t width,
                                  uint32_t height,
                                  qreal percPadding,
                                  qreal percRoundCorner,
                                  qreal inclinationDegrees = 45.0);

    static qreal angleBetweenThreePoints(QPointF center, QPointF p1, QPointF p2);
    static qreal distanceBetweenTwoPoints(QPointF p1, QPointF p2);


};

#endif // DRAWER_H
