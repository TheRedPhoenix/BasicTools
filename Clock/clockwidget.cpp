#include "clockwidget.h"
#include "clockhanddrawer.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

const double kRelativeSecondsMovementAngle = 360.0 / 60.0;
const double kRelativeMinutesSecondsMovementAngle = 360.0 / 60.0;
const double kRelativeHoursSecondsMovementAngle = 360.0 / 12.0;

const double kDeltaMinuteHandContinousMovement = kRelativeMinutesSecondsMovementAngle / 60.0;
const double kDeltaHourHandContinousMovement = kRelativeHoursSecondsMovementAngle / 60.0;

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(400,400);
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this,
            static_cast<void (ClockWidget::*)(void)>(&ClockWidget::update));
    m_timer.start();
}

ClockWidget::~ClockWidget()
{

}

RotationTuple ClockWidget::timeToRotations(QTime time, bool continousMovement)
{
    double secondsAngle = time.second()  * kRelativeSecondsMovementAngle;
    double minutesAngle = time.minute() * kRelativeMinutesSecondsMovementAngle
            + (continousMovement ? time.second()  * kDeltaMinuteHandContinousMovement : 0);
    double hoursAngle = time.hour() * kRelativeHoursSecondsMovementAngle
            + (continousMovement ? time.minute()  * kDeltaHourHandContinousMovement : 0);

    return std::make_tuple(hoursAngle,minutesAngle,secondsAngle);
}

void ClockWidget::paintEvent(QPaintEvent *event)
{
    QTime currentTime = QDateTime::currentDateTime().time();

    RotationTuple rt = timeToRotations(currentTime, true);

    ClockHandSettings secondsHandSettings = ClockHandSettings(this->rect().size(),
                                                              QSizeF(0.05, 0.43),
                                                              0.3,
                                                              0.8,
                                                              ClockHandSettings::GenericHand,
                                                              std::get<2>(rt));

    ClockHandSettings minutesHandSettings = ClockHandSettings(this->rect().size(),
                                                              QSizeF(0.1, 0.38),
                                                              0.1,
                                                              1,
                                                              ClockHandSettings::GenericHand,
                                                              std::get<1>(rt));

    ClockHandSettings hoursHandSettings = ClockHandSettings(this->rect().size(),
                                                              QSizeF(0.1, 0.25),
                                                              0.1,
                                                              1,
                                                              ClockHandSettings::GenericHand,
                                                              std::get<0>(rt));


    QPen handPen(Qt::white, 1.0);
    QBrush handBrush(Qt::black, Qt::SolidPattern);

    QPainter painter(this);
    {
        painter.save();
        painter.setPen(QPen(Qt::cyan, 1.5));
        QPoint center = this->rect().center();
        for(qreal t = 0; t <= 2*M_PI; t += 2*M_PI/60.0){
            painter.drawLine(QPointF(center),
                             QPointF(center) + QPointF(this->width()/2.0 * qCos(t), this->height()/2.0 * qSin(t)));
        }
        painter.restore();
    }

    {
        painter.save();
        painter.setPen(QPen(Qt::red, 3));
        QPoint center = this->rect().center();
        for(qreal t = 0; t <= 2*M_PI; t += 2*M_PI/12.0){
            painter.drawLine(QPointF(center),
                             QPointF(center) + QPointF(this->width()/2.0 * qCos(t), this->height()/2.0 * qSin(t)));
        }
        painter.restore();
    }

    painter.save();
    painter.setPen(handPen);
    painter.setBrush(handBrush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawPath(ClockHandDrawer::createHand(minutesHandSettings));
    painter.drawPath(ClockHandDrawer::createHand(secondsHandSettings));
    painter.drawPath(ClockHandDrawer::createHand(hoursHandSettings));
    painter.restore();

    event->accept();
}

