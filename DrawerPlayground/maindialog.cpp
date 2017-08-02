#include "maindialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QMap>
#include "basicdrawer.h"
#include "clockhanddrawer.h"


MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    m_tabWidget = new QTabWidget(this);
    mainLayout->addWidget(m_tabWidget);


    m_tabWidget->addTab(createHandWidget(), "Clock hands");
    m_tabWidget->addTab(createErrorLabelWidget(), "Error Labels");
    m_tabWidget->addTab(createWarningLabelWidget(), "Warning Labels");
}

MainDialog::~MainDialog()
{

}

QWidget *MainDialog::createWarningLabelWidget()
{
    QWidget * widget = new QWidget();
    QGridLayout * layout = new QGridLayout(widget);
    QList<QColor> foregroundColors = QList<QColor>() << QColor(Qt::red)
                                                     << QColor(Qt::white)
                                                     << QColor(Qt::black)
                                                     << QColor(Qt::yellow)
                                                     << QColor(Qt::cyan)
                                                     << QColor(Qt::blue);

    int itemPerRow = 3;

    for(int i = 0; i < foregroundColors.count(); i++){
        QLabel * label = new QLabel(widget);
        int row = i / itemPerRow;
        int column = i % itemPerRow;
        label->setPixmap(BasicDrawer::warningIcon(QSize(300,300), foregroundColors.at(i), QColor(0,0,0,0)));
        layout->addWidget(label,  row, column, 1, 1);
    }

    return widget;
}

QWidget *MainDialog::createErrorLabelWidget()
{
    QWidget * widget = new QWidget();
    QGridLayout * layout = new QGridLayout(widget);
    QList<QColor> foregroundColors = QList<QColor>() << QColor(Qt::red)
                                                     << QColor(Qt::white)
                                                     << QColor(Qt::black)
                                                     << QColor(Qt::yellow)
                                                     << QColor(Qt::cyan)
                                                     << QColor(Qt::blue);

    int itemPerRow = 3;

    for(int i = 0; i < foregroundColors.count(); i++){
        QLabel * label = new QLabel(widget);
        int row = i / itemPerRow;
        int column = i % itemPerRow;
        label->setPixmap(BasicDrawer::errorIcon(QSize(300,300), foregroundColors.at(i), QColor(0,0,0,0)));
        layout->addWidget(label,  row, column, 1, 1);
    }

    return widget;
}

QWidget *MainDialog::createHandWidget()
{
    QWidget * widget = new QWidget();
    QGridLayout * layout = new QGridLayout(widget);

    QSize pixmapSize(600,600);
    QPen pen(Qt::black, 1.0);
    QBrush brush(Qt::black, Qt::SolidPattern);

    QMap<ClockHandSettings::HandType, QList<QSizeF> > sizeMap;
    sizeMap.insert(ClockHandSettings::GenericHand, QList<QSizeF>() << QSizeF(0.05,0.43) << QSizeF(0.1,0.38) << QSizeF(0.1,0.25));
    sizeMap.insert(ClockHandSettings::RectHand, QList<QSizeF>() << QSizeF(0.025,0.43) << QSizeF(0.04,0.38) << QSizeF(0.04,0.25));

    QList<ClockHandSettings> settingsList =
            QList<ClockHandSettings>() << ClockHandSettings(pixmapSize,
                                                            QSizeF(0,0),
                                                            0,
                                                            0.8,
                                                            ClockHandSettings::GenericHand,
                                                            0)
                                       << ClockHandSettings(pixmapSize,
                                                            QSizeF(0,0),
                                                            0,
                                                            0.8,
                                                            ClockHandSettings::RectHand,
                                                            0);

    qreal rotations[3] = {45, -45, 0};
    qreal tails[3] = {0.3, 0.1, 0.1};
    qreal peakPerc[3] = {0.8, 1, 1};


    int itemPerRow = 3;
    for(int i = 0; i < settingsList.count(); i++){
        QLabel * label = new QLabel(widget);
        int row = i / itemPerRow;
        int column = i % itemPerRow;
        QPixmap pixmap(pixmapSize);
        pixmap.fill(QColor(0,0,0,0));

        QPainter p(&pixmap);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(pen);
        p.drawEllipse(QPoint(pixmapSize.width() / 2.0, pixmapSize.height() / 2.0),
                      0.9 *pixmapSize.width() / 2.0,
                      0.9 * pixmapSize.height() / 2.0);
        p.setPen(QPen(Qt::white));
        p.setBrush(brush);

        for(int j = 0; j < 3; j++){
            ClockHandSettings  chs = settingsList.at(i);
            chs.setRotation(rotations[j]);
            chs.setTailPercLength(tails[j]);
            chs.setPeakPercSize(peakPerc[j]);
            chs.setHandPercSize(sizeMap.value(chs.type()).at(j));
            p.drawPath(ClockHandDrawer::createHand(chs));
        }

        label->setPixmap(pixmap);
        layout->addWidget(label, row, column, 1, 1);

    }

    return widget;

}
