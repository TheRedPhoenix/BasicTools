#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class UdpReceiver : public QObject
{
    Q_OBJECT
public:
    explicit UdpReceiver(QObject *parent = 0);
    ~UdpReceiver();
    bool configure(const QHostAddress &address,
                   const uint32_t &port,
                   QAbstractSocket::BindMode bindMode = QAbstractSocket::DefaultForPlatform);
    bool start();

signals:
    void incomingData(QByteArray message);

private slots:
    void onUdpSocketReadyRead();

private:
    QUdpSocket::BindMode m_bindMode;
    QHostAddress m_address;
    uint32_t m_port;
    QUdpSocket * m_udpSocket;
};

#endif // UDPRECEIVER_H
