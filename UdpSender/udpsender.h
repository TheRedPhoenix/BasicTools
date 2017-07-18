#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT
public:
    explicit UdpSender(QObject *parent = 0);

    bool configure(const QHostAddress &address,
                   const uint32_t &port);
    bool sendDatagram(const QByteArray &datagram);

signals:

public slots:

private:
    QHostAddress m_address;
    uint32_t m_port;
    QUdpSocket * m_udpSocket;
};

#endif // UDPSENDER_H
