#ifndef UTILITIES_H
#define UTILITIES_H

#include <Qt>
#include <QDebug>
namespace Utilities {
    qreal rangeCheck(qreal value, qreal min, qreal max, bool *adjusted);
    qreal rangeCheck(qreal value, qreal min, qreal max);

    QStringList numberStringList(int first, int last, int step = 1);

}
#endif // UTILITIES_H
