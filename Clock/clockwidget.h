#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QTimer>


class QTimer;
typedef std::tuple<double,double,double> RotationTuple;

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    ClockWidget(QWidget *parent = 0);
    ~ClockWidget();

private:
    RotationTuple timeToRotations(QTime time, bool continousMovement = true);

    virtual void paintEvent(QPaintEvent *event) override;

    QTimer m_timer;

};

#endif // CLOCKWIDGET_H
