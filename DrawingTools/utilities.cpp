#include "utilities.h"

namespace Utilities {

qreal rangeCheck(qreal value, qreal min, qreal max, bool *adjusted)
{
    qreal adjustedValue = value;

    if(value < min){
        adjustedValue = min;
        *adjusted = true;
    } else if(value > max) {
        adjustedValue = max;
        *adjusted = true;
    }

    return adjustedValue;

}

qreal rangeCheck(qreal value, qreal min, qreal max)
{
    bool unused;
    return rangeCheck(value, min, max, &unused);
}

}
