#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QDialog>
#include <QTimer>
#include "udpsender.h"

namespace Ui {
class NetworkWidget;
}

class NetworkWidget : public QDialog
{
    Q_OBJECT
public:
    enum State {
        Running = 0,
        Paused = 1,
        Stopped = 2
    };

    explicit NetworkWidget(QWidget *parent = 0);
    ~NetworkWidget();

    void refreshHostAddressList();

private slots:
    void updateButtonState();
    void onTimeout();

    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    QTimer m_timer;
    State m_state;
    UdpSender *m_sender;
    Ui::NetworkWidget *ui;
};

#endif // NETWORKWIDGET_H
