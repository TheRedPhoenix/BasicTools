#include "basicdrawer.h"
#include <QPainter>
#include <QtMath>
#include <QFont>
#include "utilities.h"

BasicDrawer::BasicDrawer()
{

}

QPixmap BasicDrawer::warningIcon(QSize size, QColor foreground, QColor background)
{
    QPixmap pixmap(size);
    pixmap.fill(background);

    QPainter painter(&pixmap);
    QPen pen(QBrush(Qt::black), 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(QBrush(foreground));
    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal padding = 0.1;
    qreal roundPercentage = 0.1;

    QPainterPath path = trianglePath(size.width(), size.height(), padding, roundPercentage);
    painter.drawPath(path);

    QPainterPath markPath;
    QFont f("Times New Roman", 0.95 * size.height() * ( 1 - 2 * padding - roundPercentage) );
    QString markText("!");
    QFontMetrics metrics(f);
    QPointF basePoint((size.width() - metrics.width(markText)) / 2.0, 0.95 * size.height() * ( 1 - padding));
    markPath.addText(basePoint, f, markText);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawPath(markPath);

    return pixmap;
}

QPixmap BasicDrawer::errorIcon(QSize size, QColor foreground, QColor background)
{
    QPixmap pixmap(size);
    pixmap.fill(background);

    QPainter painter(&pixmap);
    QPen pen(QBrush(Qt::black), 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(QBrush(foreground));
    painter.setRenderHint(QPainter::Antialiasing, true);

    qreal padding = 0.1;
    qreal roundPercentage = 0.1;

    QPainterPath path = crossPath(size.width(), size.height(), padding, roundPercentage, 45.0);

    painter.drawPath(path);
    return pixmap;
}

QPainterPath BasicDrawer::trianglePath(uint32_t width, uint32_t height, qreal percPadding, qreal percRoundCorner)
{
    bool adjusedValue;
    percPadding = Utilities::rangeCheck(percPadding, 0,0.5, &adjusedValue);

    qreal wPadding = width  * percPadding;
    qreal hPadding = height * percPadding;

    QPointF topVertex(width / 2.0, + hPadding);
    QPointF bottomLeftVertex(0+wPadding, height - hPadding);
    QPointF bottomRightVertex(width-wPadding, height - hPadding);

    qreal roundRadius = qMin(percRoundCorner * width, percRoundCorner * height);

    qreal bottomLeftAngle = angleBetweenThreePoints(bottomLeftVertex, topVertex, bottomRightVertex);
    qreal bottomRightAngle = angleBetweenThreePoints(bottomRightVertex, topVertex, bottomLeftVertex);
    qreal topAngle = angleBetweenThreePoints(topVertex, bottomLeftVertex, bottomRightVertex);

    // bottom left
    QPointF bottomLeftVertex_roundedTop = bottomLeftVertex + QPointF(roundRadius * qCos(bottomLeftAngle), - roundRadius * qSin(bottomLeftAngle));
    QPointF bottomLeftVertex_roundedBottom = bottomLeftVertex + QPointF(roundRadius, 0);

    // bottom right
    QPointF bottomRightVertex_roundedTop = bottomRightVertex - QPointF(roundRadius * qCos(bottomRightAngle), roundRadius * qSin(bottomRightAngle));
    QPointF bottomRightVertex_roundedBottom = bottomRightVertex - QPointF(roundRadius, 0);

    // top
    QPointF topVertex_roundedRight = topVertex + QPointF(roundRadius * qSin(topAngle / 2.0), roundRadius * qCos(topAngle / 2.0));
    QPointF topVertex_roundedLeft = topVertex + QPointF( - roundRadius * qSin(topAngle / 2.0), roundRadius * qCos(topAngle / 2.0));

    QPainterPath path;
    path.moveTo(topVertex_roundedLeft);
    path.lineTo(bottomLeftVertex_roundedTop);
    path.quadTo(bottomLeftVertex, bottomLeftVertex_roundedBottom);
    path.lineTo(bottomRightVertex_roundedBottom);
    path.quadTo(bottomRightVertex, bottomRightVertex_roundedTop);
    path.lineTo(topVertex_roundedRight);
    path.quadTo(topVertex, topVertex_roundedLeft);
    path.closeSubpath();
    return path;
}

QPainterPath BasicDrawer::crossPath(uint32_t width, uint32_t height, qreal percPadding, qreal percRoundCorner, qreal inclinationDegrees)
{
    bool adjusted;

    percPadding = Utilities::rangeCheck(percPadding, 0, 0.5, &adjusted);
    inclinationDegrees = Utilities::rangeCheck(inclinationDegrees, 0, 90, &adjusted);

    qreal wPadding = width  * percPadding;
    qreal hPadding = height * percPadding;
    qreal paddedWidth = width-wPadding;
    qreal paddedHeigth = height - hPadding;

    qreal percArmSize = 0.05 * qMin(paddedWidth, paddedHeigth);

    qreal xArmSizeProjLenght = percArmSize * qCos(qDegreesToRadians(inclinationDegrees));
    qreal yArmSizeProjLenght = percArmSize * qSin(qDegreesToRadians(inclinationDegrees));

    QPainterPath path;
    path.moveTo(width/2.0 - xArmSizeProjLenght, height/2.0);
    path.lineTo(width/2.0, height/2.0 + yArmSizeProjLenght);
    path.lineTo(width/2.0 + xArmSizeProjLenght, height/2.0);
    path.lineTo(width/2.0, height/2.0 - yArmSizeProjLenght);
    path.closeSubpath();

    return path;

}

qreal BasicDrawer::angleBetweenThreePoints(QPointF center, QPointF p1, QPointF p2)
{
    qreal c_p1 = distanceBetweenTwoPoints(center, p1);
    qreal c_p2 = distanceBetweenTwoPoints(center, p2);
    qreal p1_p2 = distanceBetweenTwoPoints(p1, p2);

    // angle in radians
    return qAcos((pow(c_p1, 2) + pow(c_p2, 2) - pow(p1_p2, 2)) / (2 * c_p1 * c_p2 ));
}

qreal BasicDrawer::distanceBetweenTwoPoints(QPointF p1, QPointF p2)
{
    return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(),2));
}

