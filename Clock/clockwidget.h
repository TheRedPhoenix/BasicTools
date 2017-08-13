#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QStaticText>

class QTimer;

typedef std::tuple<double,double,double> RotationTuple;
typedef QPair<QPointF, QStaticText> TextData;
typedef QVector<TextData> TextDataVector;

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    ClockWidget(QWidget *parent = 0);
    ~ClockWidget();

    QFont hourLabelFont() const;
    void setHourLabelFont(const QFont &hourLabelFont);

private:
    RotationTuple timeToRotations(QTime time, bool continousMovement = true);

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    void build();
    void buildHands();
    void buildText(const qreal &screenSide);
    void buildCrown(const qreal &screenSide);

    TextDataVector createLabelVector(const qreal centerRadius,
                                    const QFont &labelFont,
                                    const QStringList &textList,
                                     QVector<QRectF> * rectVector = nullptr);
    QTimer m_timer;

    QPainterPath m_hoursHand;
    QPainterPath m_minutesHand;
    QPainterPath m_secondsHand;
    QSize m_clockScreenSize;


    QFont m_hourLabelFont;
    TextDataVector m_hourLabelsVector;
    QVector<QRectF> m_hourLabelRectVector;

    QPainterPath m_screenCrown;
    QPointF m_screenCenter;

};

#endif // CLOCKWIDGET_H
