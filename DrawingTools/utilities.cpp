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

QStringList numberStringList(int first, int last, int step)
{
    Q_ASSERT_X(first <= last - step, "Utilities::numberStringList", "Error in function arguments");

    QStringList numberList;
    for(int i = first; i <= last; i+=step){
        numberList << QString::number(i, 10);
    }

    return numberList;
}



}
