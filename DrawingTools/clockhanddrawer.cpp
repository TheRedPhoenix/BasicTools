#include "clockhanddrawer.h"

#include "basicdrawer.h"
#include "utilities.h"

ClockHandDrawer::ClockHandDrawer()
{

}

QPainterPath ClockHandDrawer::createHand(const ClockHandSettings &settings)
{
    QPainterPath handPath;

    QRect screenRect(QPoint(0,0), settings.screenSize());

    if(settings.originLocation() == ClockHandSettings::Center){
        QPoint center = QPoint(0,0);
        screenRect.moveCenter(center);
    }


    switch(settings.type()){

    case ClockHandSettings::GenericHand:
        handPath = genericHand(screenRect,
                               settings.handPercSize(),
                               settings.tailPercLength(),
                               settings.peakPercSize(),
                               settings.rotation());
        break;
    case ClockHandSettings::RectHand   :
        handPath = genericHand(screenRect,
                               settings.handPercSize(),
                               settings.tailPercLength(),
                               0,
                               settings.rotation());
        break;
    case ClockHandSettings::HandMax    :
    default:
        break;
    }

    return handPath;
}


QPainterPath ClockHandDrawer::genericHand(const QRect &screenRect, const QSizeF &handPercSize, qreal tailPercLength, qreal peakPercentage, qreal rotation)
{
    QSize screenSize = screenRect.size();
    QSizeF handSize = QSizeF(handPercSize.width() * screenSize.width(), handPercSize.height() * screenSize.height());

    qreal tailLength = tailPercLength * handSize.height();

    qreal halfWidth = handSize.width() / 2.0;

    // avoid tailLenght to be less than zero
    tailLength = qMax(tailLength, 0.0);

    qreal tipWidth = halfWidth * (1 - peakPercentage);

    QPainterPath hand;
    // Point 0
    hand.moveTo(screenRect.center() + QPointF( 0, -handSize.height()));
    // Point 1
    hand.lineTo(screenRect.center() + QPointF(tipWidth, -handSize.height()));
    // Point 3
    hand.lineTo(screenRect.center() + QPointF( halfWidth, 0));
    // Point 4
    hand.lineTo(screenRect.center() + QPointF( tipWidth, qMax(halfWidth, tailLength)));
    // Point 5
    hand.lineTo(screenRect.center() + QPointF( 0, qMax(halfWidth, tailLength)));

    QTransform reflectionTransform;
    reflectionTransform.translate(screenRect.center().x(), screenRect.center().y());
    reflectionTransform.rotate(180, Qt::YAxis);
    reflectionTransform.translate(-screenRect.center().x(), -screenRect.center().y());

    hand.connectPath(reflectionTransform.map(hand));
    hand = hand.simplified();

    QTransform rotationTransform;
    rotationTransform.translate(screenRect.center().x(), screenRect.center().y());
    rotationTransform.rotate(rotation);
    rotationTransform.translate(-screenRect.center().x(), -screenRect.center().y());

    return rotationTransform.map(hand);
}
