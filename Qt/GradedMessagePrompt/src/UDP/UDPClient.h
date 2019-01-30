#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class UDPClient : public QObject
{
    Q_OBJECT
public:
    explicit UDPClient();
    ~UDPClient();
    void writeBytes(QByteArray& bytes, QHostAddress
            hostAddr = QHostAddress("127.0.0.1"),quint16 port = 6000);

    void setHost(const QString addr,const quint16 port = 6001);
signals:
    void recvBytes(QByteArray bytes);
private:
    void _received();

    QUdpSocket*         _udpClient;
    QHostAddress        _hostAddr;
    quint16             _port;
};

#endif // UDPCLIENT_H
