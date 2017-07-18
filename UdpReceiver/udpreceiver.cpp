#include "udpreceiver.h"

UdpReceiver::UdpReceiver(QObject *parent)
    : m_address(QHostAddress())
    , m_port(0)
    , m_udpSocket(nullptr)
    , QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpReceiver::onUdpSocketReadyRead);
}

UdpReceiver::~UdpReceiver()
{
}

bool UdpReceiver::configure(const QHostAddress &address, const uint32_t &port, QAbstractSocket::BindMode bindMode)
{
    bool configurationIsOk = !address.isNull() && port != 0;

    if(configurationIsOk){
        m_address = address;
        m_port = port;
        m_bindMode = bindMode;
    }

    return configurationIsOk;
}


bool UdpReceiver::start()
{
    bool socketBounded = false;

    if(!m_address.isNull() && m_port != 0){
        socketBounded = m_udpSocket->bind(m_address, m_port, m_bindMode);
    }

    return socketBounded;
}

void UdpReceiver::onUdpSocketReadyRead()
{
    if(m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                  &sender, &senderPort);

        emit incomingData(datagram);
    }
}
