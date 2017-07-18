#include "networkwidget.h"
#include <QNetworkInterface>

#include "ui_networkwidget.h"

NetworkWidget::NetworkWidget(QWidget *parent) :
    QDialog(parent),
    m_sender(nullptr),
    m_state(Stopped),
    ui(new Ui::NetworkWidget)
{
    ui->setupUi(this);

    connect(&m_timer, &QTimer::timeout, this, &NetworkWidget::onTimeout);

    refreshHostAddressList();
    updateButtonState();


}

NetworkWidget::~NetworkWidget()
{
    delete ui;
}

void NetworkWidget::refreshHostAddressList()
{
    ui->addressCombobox->clear();

    foreach(const QHostAddress &address, QNetworkInterface::allAddresses()){
        if (address.protocol() == QAbstractSocket::IPv4Protocol){
            ui->addressCombobox->addItem(address.toString());
        }
    }
}

void NetworkWidget::updateButtonState()
{
    ui->startButton->setEnabled(m_state == Stopped || m_state == Paused);
    ui->stopButton->setEnabled(m_state == Running || m_state == Paused);
    ui->pauseButton->setEnabled(m_state == Running);
}

void NetworkWidget::onTimeout()
{
    QByteArray message;
    QDataStream stream(&message, QIODevice::WriteOnly );
    stream << ui->messageLineEdit->text();

    if(m_sender->sendDatagram(ui->messageLineEdit->text().toLatin1() /*message*/)){
        ui->lcdNumber->display(ui->lcdNumber->intValue() + 1);
    }
}
void NetworkWidget::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);

    if(m_state == Paused){
        m_timer.start();
        m_state = Running;
    } else if(m_state == Stopped){

        if(m_sender){
            m_sender->deleteLater();
        }

        m_sender = new UdpSender(this);
        bool canConfigure = m_sender->configure(QHostAddress(ui->addressCombobox->currentText()),
                                                ui->portSpinBox->value());

        if(canConfigure) {
            m_state = Running;
            ui->addresseeGroupbox->setEnabled(false);
            m_timer.setInterval(1000/ui->frequencySpinBox->value());
            m_timer.start();
        } else {
            m_state = Stopped;
        }

    }

    updateButtonState();
}

void NetworkWidget::on_pauseButton_clicked()
{
    ui->pauseButton->setEnabled(false);

    if(m_timer.isActive()){
        m_timer.stop();
        m_state = Paused;
    }

    updateButtonState();

}

void NetworkWidget::on_stopButton_clicked()
{
    ui->stopButton->setEnabled(false);
    m_timer.stop();
    m_state = Stopped;
    ui->lcdNumber->display(0);
    ui->addresseeGroupbox->setEnabled(true);
    updateButtonState();
}
