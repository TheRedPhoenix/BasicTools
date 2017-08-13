#include "clockwidget.h"
#include "clockhanddrawer.h"

#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QTextFormat>
#include "utilities.h"

const double kRelativeSecondsMovementAngle = 360.0 / 60.0;
const double kRelativeMinutesSecondsMovementAngle = 360.0 / 60.0;
const double kRelativeHoursSecondsMovementAngle = 360.0 / 12.0;

const double kDeltaMinuteHandContinousMovement = kRelativeMinutesSecondsMovementAngle / 60.0;
const double kDeltaHourHandContinousMovement = kRelativeHoursSecondsMovementAngle / 60.0;

const double kScreenSizeScaleFactor = 0.7;
const double kLabelsPositionScaleFactor = 0.4;

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400,400);
    m_hourLabelFont.setPointSize(20);
    build();
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
#ifdef PAINT_DEBUG
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
#endif

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

    // Draw Crown
    /*painter.save();
    painter.setPen(QPen(Qt::black, 2));
    painter.drawPath(m_screenCrown);
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRects(m_hourLabelRectVector);
    painter.restore();*/


    // Hours Label

#ifdef PAINT_DEBUG
    painter.save();
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawRects(m_hourLabelRectVector);
    painter.restore();
#endif

    painter.save();
    painter.setFont(m_hourLabelFont);
    painter.setPen(QPen(Qt::black, 2));
    foreach(const TextData &data, m_hourLabelsVector){
        painter.drawStaticText(data.first, data.second);
    }
    painter.restore();



    event->accept();
}

void ClockWidget::resizeEvent(QResizeEvent *event)
{
    build();
    QWidget::resizeEvent(event);
}

void ClockWidget::build()
{
    // normalizing rect size
    int side = qMin(this->rect().width(), this->rect().height());

    m_screenCenter = QPointF(this->rect().width() / 2.0, this->rect().height() / 2.0);
    m_clockScreenSize = QSize(side * kScreenSizeScaleFactor,
                              side * kScreenSizeScaleFactor);

    buildHands();
    buildText(side);
//    buildCrown(side);

}

void ClockWidget::buildText(const qreal &screenSide)
{
    m_hourLabelRectVector.clear();
    m_hourLabelsVector = createLabelVector(screenSide * kLabelsPositionScaleFactor,
                                           m_hourLabelFont,
                                           Utilities::numberStringList(1, 12, 1),
                                           &m_hourLabelRectVector);
}

void ClockWidget::buildCrown(const qreal &screenSide)
{
    QPainterPath screenCrown;
    screenCrown.addEllipse(m_screenCenter,
                                  screenSide * kLabelsPositionScaleFactor,
                                  screenSide *  kLabelsPositionScaleFactor);

    QPainterPath rectsPath;

    foreach(const QRectF &r, m_hourLabelRectVector){
        rectsPath.addRect(r);
    }

    rectsPath.translate(m_screenCenter.x(), m_screenCenter.y());

    m_screenCrown = screenCrown/*.subtracted(screenCrown.intersected(rectsPath))*/;
}

void ClockWidget::buildHands()
{

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

TextDataVector ClockWidget::createLabelVector(const qreal centerRadius, const QFont &labelFont, const QStringList &textList, QVector<QRectF> *rectVector)
{
    int numberOfRects = textList.count();

    TextDataVector vector(numberOfRects);

    qreal deltaT = 2*M_PI / numberOfRects ;

    QFontMetrics metrics(labelFont);

    int textH = metrics.height();

    int counter = 0;
    for(qreal t = - M_PI_2 + deltaT; t < 3*M_PI_2 /*+ deltaT*/; t+= deltaT){

        qreal textW = metrics.width(textList.at(counter));

        QPointF topLeftPoint(centerRadius * qCos(t) - textW / 2.0,
                             centerRadius * qSin(t) - textH / 2.0);

        vector << qMakePair(m_screenCenter + topLeftPoint, QStaticText(textList.at(counter)));

        if(rectVector != nullptr){
            (*rectVector) << QRectF(m_screenCenter + topLeftPoint, QSizeF(textW, textH) );
        }

        counter++;
    }

    return vector;

}

QFont ClockWidget::hourLabelFont() const
{
    return m_hourLabelFont;
}

void ClockWidget::setHourLabelFont(const QFont &hourLabelFont)
{
    m_hourLabelFont = hourLabelFont;
    build();
    update();
}


