#include "udpsender.h"

UdpSender::UdpSender(QObject *parent)
    : m_address(QHostAddress())
    , m_port(0)
    , m_udpSocket(nullptr)
    , QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
}


bool UdpSender::configure(const QHostAddress &address, const uint32_t &port)
{
    bool configurationIsOk = address.isNull() && port != 0;

    if(configurationIsOk){
        m_address = address;
        m_port = port;
    }

    return configurationIsOk;
}


bool UdpSender::sendDatagram(const QByteArray &datagram)
{
    qint64 bytesWritten = m_udpSocket->writeDatagram(datagram, m_address, (uint16_t)m_port);
    return bytesWritten = datagram.size();
}
