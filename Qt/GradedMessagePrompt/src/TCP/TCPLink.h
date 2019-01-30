#ifndef TCPLINK_H
#define TCPLINK_H

#include <QThread>
#include <QtNetwork>
#include <QAbstractSocket>

class TCPLink : public QThread
{
    Q_OBJECT
public:
    explicit TCPLink();
    ~TCPLink();
    bool tcpConnect(QString ip,quint16 port);
    bool isConnected(void);
    void writeBytes(const QByteArray data);

    Q_PROPERTY(int port             READ port       WRITE setPort       NOTIFY portChanged)
    Q_PROPERTY(QString ip           READ ip         WRITE setIp         NOTIFY ipChanged)
    Q_PROPERTY(bool isConnected     READ isConnected                    NOTIFY isConnectedChanged)

    Q_INVOKABLE void createlink(QString ip,quint16 port);
    Q_INVOKABLE void disconnect(void);

    quint16 port(void){return _port;}
    QString ip(void){return _ip;}
signals:
    void bytesReceived(QByteArray b);
    void isConnectedChanged(void);

    void portChanged(quint16 port);
    void ipChanged(QString ip);
public slots:
    void readBytes(void);

    void setPort(quint16 port);
    void setIp(QString ip);
private:
    QTcpSocket *_tcpSocket;
    bool _isConnected;
    quint16 _port;
    QString _ip;
};

#endif // TCPLINK_H
