#include <QDebug>
#include <QtNetwork>
#include <QThread>

#include <QTimer>
#include <QList>
#include <QDebug>
#include <QMutexLocker>
#include <QtQml>
#include "TCPLink.h"

TCPLink::TCPLink() :
  _tcpSocket(NULL)
    ,_isConnected(false)
    ,_ip("127.0.0.1")
    ,_port(4800)
{
    createlink(_ip,_port);
}

TCPLink::~TCPLink(void)
{
    quit();
    wait();
    disconnect();
}

bool TCPLink::tcpConnect(QString ip,quint16 port)
{
    Q_ASSERT(_tcpSocket == NULL);
    _tcpSocket = new QTcpSocket();

    _tcpSocket->abort();
    _tcpSocket->connectToHost(QHostAddress(ip),port);

    if(!_tcpSocket->waitForConnected(3000)){
        qDebug()<< "Connection failed";
        delete _tcpSocket;
        _tcpSocket = NULL;
        _isConnected = false;
        emit isConnectedChanged();
        return false;
    }

    connect(_tcpSocket, &QTcpSocket::readyRead,     this,   &TCPLink::readBytes);
    _isConnected = true;
    emit isConnectedChanged();
    return true;
}

void TCPLink::writeBytes(const QByteArray data){
    if(!_tcpSocket)
          return;

    if(_tcpSocket->write(data) < 0){
        qDebug()<< "send out data [" << data.data() << " ] failed !";
    }

   _tcpSocket->waitForBytesWritten(3000);
}

void TCPLink::readBytes(void)
{
    qint64 count = _tcpSocket->bytesAvailable();
    if(count){
        QByteArray recvData;
        recvData.resize(count);
        _tcpSocket->read(recvData.data(),recvData.size());
        emit bytesReceived(recvData);
    }
}

void TCPLink::disconnect(void)
{
    quit();
    wait();
    if(_tcpSocket){
        //close the socket's connection.
        _tcpSocket->disconnectFromHost();
        _tcpSocket->close();
        if(_tcpSocket->state() == QAbstractSocket::UnconnectedState ||
             _tcpSocket->waitForDisconnected(30000)){
            _tcpSocket->deleteLater();
            _tcpSocket=NULL;
            _isConnected = false;
            emit isConnectedChanged();
        }
    }
}

void TCPLink::createlink(QString ip,quint16 port)
{
    disconnect();
    if(!tcpConnect(ip,port)){
        qWarning() << "create connection failed !";
    }
}

bool TCPLink::isConnected(void)
{
    return _isConnected;
}


void TCPLink::setIp(QString ip)
{
    if(_ip != ip){
        _ip = ip;
        emit ipChanged(ip);
    }
}

void TCPLink::setPort(quint16 port)
{
    if(_port != port){
        _port = port;
        emit portChanged(port);
    }
}
