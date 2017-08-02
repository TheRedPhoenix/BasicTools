#include "clockhandsettings.h"
#include "utilities.h"

ClockHandSettings::ClockHandSettings(const QSize &screenSize, QSizeF handPercSize, qreal tailPercLength, qreal peakPercSize, HandType type, qreal rotation)
{
    setScreenSize(screenSize);
    setHandPercSize(handPercSize);
    setTailPercLength(tailPercLength);
    setPeakPercSize(peakPercSize);
    setType(type);
    setRotation(rotation);
}

QSize ClockHandSettings::screenSize() const
{
    return m_screenSize;
}

void ClockHandSettings::setScreenSize(const QSize &screenSize)
{
    m_screenSize = screenSize;
}

QSizeF ClockHandSettings::handPercSize() const
{
    return m_handPercSize;
}

void ClockHandSettings::setHandPercSize(const QSizeF &handPercSize)
{
    qreal w = Utilities::rangeCheck(handPercSize.width(), kHandPercWidthMin, kHandPercWidthMax);
    qreal h = Utilities::rangeCheck(handPercSize.height(), kHandPercHeightMin, kHandPercHeightMax);
    m_handPercSize = QSizeF(w,h);
}

qreal ClockHandSettings::tailPercLength() const
{
    return m_tailPercLength;
}

void ClockHandSettings::setTailPercLength(const qreal &tailPercLength)
{
    m_tailPercLength = Utilities::rangeCheck(tailPercLength, kTailPercLengthMin, kTailPercLengthMax);
}

qreal ClockHandSettings::peakPercSize() const
{
    return m_peakPercSize;
}

void ClockHandSettings::setPeakPercSize(const qreal &peakPercSize)
{
    m_peakPercSize = Utilities::rangeCheck(peakPercSize, kPeakPercSizeMin, kPeakPercSizeMax);
}

ClockHandSettings::HandType ClockHandSettings::type() const
{
    return m_type;
}

void ClockHandSettings::setType(const HandType &type)
{
    m_type = type;
}

qreal ClockHandSettings::rotation() const
{
    return m_rotation;
}

void ClockHandSettings::setRotation(const qreal &rotation)
{
    m_rotation = rotation;
}
