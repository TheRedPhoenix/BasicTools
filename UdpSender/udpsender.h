#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT
public:
    explicit UdpSender(QObject *parent = 0);
    explicit UdpSender(const QHostAddress & address,
                       const uint32_t &port,
                       QAbstractSocket::BindMode bindMode = QAbstractSocket::DefaultForPlatform,
                       QObject *parent = 0);

    bool configure(const QHostAddress &address,
                   const uint32_t &port,
                   QAbstractSocket::BindMode bindMode = QAbstractSocket::DefaultForPlatform);
    bool stop();
    bool start();

signals:

public slots:

private:
    QHostAddress m_address;
    uint32_t m_port;
    QUdpSocket * m_udpSocket;
    QAbstractSocket::BindMode m_bindMode;
};

#endif // UDPSENDER_H
