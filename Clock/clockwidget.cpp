#include "clockwidget.h"
#include "clockhanddrawer.h"
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>

const double kRelativeSecondsMovementAngle = 360.0 / 60.0;
const double kRelativeMinutesSecondsMovementAngle = 360.0 / 60.0;
const double kRelativeHoursSecondsMovementAngle = 360.0 / 12.0;

const double kDeltaMinuteHandContinousMovement = kRelativeMinutesSecondsMovementAngle / 60.0;
const double kDeltaHourHandContinousMovement = kRelativeHoursSecondsMovementAngle / 60.0;

const double kScreenSizeScaleFactor = 0.7;

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400,400);
    buildHands();
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

    QPen handPen(Qt::white, 1.0);
    QBrush handBrush(Qt::black, Qt::SolidPattern);

    QPainter painter(this);
    /*{
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
    }*/

    painter.save();
    painter.setPen(handPen);
    painter.setBrush(handBrush);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // translate the painter to move it in the center of the screen
    painter.translate(this->width() / 2.0, this->height() / 2.0);

    // draw seconds hand
    painter.save();
    painter.rotate(std::get<2>(rt));
    painter.drawPath(m_secondsHand);
    painter.restore();
    // draw minutes hand
    painter.save();
    painter.rotate(std::get<1>(rt));
    painter.drawPath(m_minutesHand);
    painter.restore();
    // draw hours hand
    painter.save();
    painter.rotate(std::get<0>(rt));
    painter.drawPath(m_hoursHand);
    painter.restore();

    painter.restore();

    event->accept();
}

void ClockWidget::resizeEvent(QResizeEvent *event)
{
    buildHands();
    QWidget::resizeEvent(event);
}

void ClockWidget::buildHands()
{
    // normalizing rect size
    int side = qMin(this->rect().width(), this->rect().height());

    m_clockScreenSize = QSize(side * kScreenSizeScaleFactor,
                              side * kScreenSizeScaleFactor);

    ClockHandSettings secondsHandSettings = ClockHandSettings(m_clockScreenSize,
                                                              ClockHandSettings::Center,
                                                              QSizeF(0.05, 0.43),
                                                              0.3,
                                                              0.8,
                                                              ClockHandSettings::GenericHand,
                                                              0);

    ClockHandSettings minutesHandSettings = ClockHandSettings(m_clockScreenSize,
                                                              ClockHandSettings::Center,
                                                              QSizeF(0.1, 0.38),
                                                              0.1,
                                                              1,
                                                              ClockHandSettings::GenericHand,
                                                              0);

    ClockHandSettings hoursHandSettings = ClockHandSettings(m_clockScreenSize,
                                                            ClockHandSettings::Center,
                                                            QSizeF(0.1, 0.25),
                                                            0.1,
                                                            1,
                                                            ClockHandSettings::GenericHand,
                                                            0);


    m_hoursHand    = ClockHandDrawer::createHand(hoursHandSettings);
    m_minutesHand  = ClockHandDrawer::createHand(minutesHandSettings);
    m_secondsHand  = ClockHandDrawer::createHand(secondsHandSettings);

}

