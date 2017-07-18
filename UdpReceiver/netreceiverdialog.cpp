#include "netreceiverdialog.h"
#include "ui_netreceiverdialog.h"

#include <QNetworkInterface>
#include <QTextCodec>

#include <QDebug>

NetReceiverDialog::NetReceiverDialog(QWidget *parent) :
    QDialog(parent),
    m_receiver(nullptr),
    ui(new Ui::NetReceiverDialog)
{
    ui->setupUi(this);
    refreshHostAddressList();
}

NetReceiverDialog::~NetReceiverDialog()
{
    delete ui;
}

void NetReceiverDialog::refreshHostAddressList()
{
    ui->addressCombobox->clear();

    foreach(const QHostAddress &address, QNetworkInterface::allAddresses()){
        if (address.protocol() == QAbstractSocket::IPv4Protocol){
            ui->addressCombobox->addItem(address.toString());
        }
    }

}

void NetReceiverDialog::processIncomingData(const QByteArray &message)
{
    ui->listWidget->addItem(new QListWidgetItem(QString::fromLatin1(message)));
    ui->listWidget->scrollToBottom();
}

void NetReceiverDialog::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);

    if(m_receiver){
        m_receiver->deleteLater();
    }

    m_receiver = new UdpReceiver(this);
    connect(m_receiver, &UdpReceiver::incomingData, this, &NetReceiverDialog::processIncomingData);

    if(m_receiver->configure(QHostAddress(ui->addressCombobox->currentText()),ui->portSpinBox->value())){
        m_receiver->start();
        ui->stopButton->setEnabled(true);
    } else {
        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
    }

}

void NetReceiverDialog::on_stopButton_clicked()
{
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
}
