#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QThread>
#include <QMap>
#include <QUdpSocket>
#include <QHostInfo>

class UDPServer : public QThread
{
    Q_OBJECT
public:
    explicit UDPServer();
    ~UDPServer();
    virtual void run() final;
    void writeToHost(QByteArray byte,QString dstAddr,quint16 port);
signals:
    void recvBytes(QByteArray bytes,QString addr,quint16 port);
    void _writeToHostSingal(const QByteArray&, QString addr,quint16 port);
private slots:
    void _received();
    void _writeToHostSlot(const QByteArray& data,QString dstAddr,quint16 dstPort);
private:
    QUdpSocket*     _udpsocket;
    quint16         _port;
    QString         _address;
};

#endif // UDPSERVER_H
