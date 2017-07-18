#ifndef NETRECEIVERDIALOG_H
#define NETRECEIVERDIALOG_H

#include <QDialog>
#include "udpreceiver.h"

namespace Ui {
class NetReceiverDialog;
}

class NetReceiverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetReceiverDialog(QWidget *parent = 0);
    ~NetReceiverDialog();

    void refreshHostAddressList();

private slots:
    void processIncomingData(const QByteArray &message);

    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::NetReceiverDialog *ui;
    UdpReceiver * m_receiver;
};

#endif // NETRECEIVERDIALOG_H
