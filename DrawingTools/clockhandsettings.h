#ifndef CLOCKHANDSETTINGS_H
#define CLOCKHANDSETTINGS_H

#include <QSizeF>
#include <QTime>

const qreal kHandPercWidthMin = 0.02;
const qreal kHandPercWidthMax = 0.5;

const qreal kHandPercHeightMin = 0.02;
const qreal kHandPercHeightMax = 0.5;

const qreal kTailPercLengthMin = 0.0;
const qreal kTailPercLengthMax = 0.4;

const qreal kPeakPercSizeMin = 0.0;
const qreal kPeakPercSizeMax = 1;

class ClockHandSettings
{
public:
    enum HandType {
        GenericHand,
        RectHand,
        HandMax
    };

    enum OriginLocation {
        TopLeft,
        Center
    };

    ClockHandSettings(const QSize &screenSize,
                      OriginLocation location = TopLeft,
                      QSizeF handPercSize = QSizeF(0.1,0.45),
                      qreal tailPercLength = 0.3,
                      qreal peakPercSize = 1.0,
                      HandType type = GenericHand,
                      qreal rotation = 0.0);

    QSize screenSize() const;
    void setScreenSize(const QSize &screenSize);

    QSizeF handPercSize() const;
    void setHandPercSize(const QSizeF &handPercSize);

    qreal tailPercLength() const;
    void setTailPercLength(const qreal &tailPercLength);

    qreal peakPercSize() const;
    void setPeakPercSize(const qreal &peakPercSize);

    HandType type() const;
    void setType(const HandType &type);

    qreal rotation() const;
    void setRotation(const qreal &rotation);

    OriginLocation originLocation() const;
    void setOriginLocation(const OriginLocation &originLocation);

private:
    QSize m_screenSize;
    QSizeF m_handPercSize;
    qreal m_tailPercLength;
    qreal m_peakPercSize;
    HandType m_type;
    OriginLocation m_originLocation;
    qreal m_rotation;
};

#endif // CLOCKHANDSETTINGS_H
