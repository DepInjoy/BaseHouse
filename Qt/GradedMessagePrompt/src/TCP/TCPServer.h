#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QThread>
#include <QtNetwork>

class TCPServer : public QThread
{
    Q_OBJECT
public:
    explicit TCPServer();
    ~TCPServer();
signals:
    void bytesReceived(QByteArray b);
protected:
    virtual void run(void);
public slots:
private slots:
    void _connection(void);
    void readBytes();
private:
    QTcpSocket *_tcpSocket;
    QTcpServer *_tcpServer;
    QString _ipAddr;
    quint16 _port;
};

#endif // TCPSERVER_H
