#ifndef CLOCKHANDDRAWER_H
#define CLOCKHANDDRAWER_H

#include <QPainterPath>
#include "basicdrawer.h"

#include "clockhandsettings.h"

class ClockHandDrawer
{
public:

    ClockHandDrawer();

    static QPainterPath createHand(const ClockHandSettings &settings);

private:
    static QPainterPath genericHand(const QRect &screenRect,
                                    const QSizeF &handSize,
                                    qreal tailLength = 0,
                                    qreal peakPercentage = 0,
                                    qreal rotation = 0);

};

#endif // CLOCKHANDDRAWER_H
