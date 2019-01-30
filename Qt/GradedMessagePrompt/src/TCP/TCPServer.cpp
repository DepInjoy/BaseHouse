#include "TCPServer.h"

TCPServer::TCPServer():
    _tcpSocket(NULL)
  ,_tcpServer(NULL)
  ,_ipAddr("127.0.0.1")
  ,_port(4800)
{
    moveToThread(this);
    start(HighPriority);
}

TCPServer::~TCPServer()
{
    quit();
    wait();

    if(_tcpServer){
        _tcpServer->deleteLater();
        _tcpServer = NULL;
    }

    if(_tcpSocket){
        _tcpSocket->disconnectFromHost();
        _tcpSocket->close();
        if(_tcpSocket->state() == QAbstractSocket::UnconnectedState ||
             _tcpSocket->waitForDisconnected(3000)){
            _tcpSocket->deleteLater();
            _tcpSocket = NULL;
        }
    }
}

void TCPServer::run()
{
    _tcpServer = new QTcpServer();
    connect(_tcpServer,&QTcpServer::newConnection,this,&TCPServer::_connection);
    _tcpServer->listen(QHostAddress(_ipAddr),_port);
    exec();
}

void TCPServer::_connection(void)
{
    _tcpSocket = _tcpServer->nextPendingConnection();
    Q_ASSERT(_tcpSocket);
    connect(_tcpSocket,&QTcpSocket::readyRead,this,&TCPServer::readBytes);
}

void TCPServer::readBytes(void)
{
    qint64 count = _tcpSocket->bytesAvailable();
    if(count){
        QByteArray recvData;
        recvData.resize(count);
        _tcpSocket->read(recvData.data(),recvData.size());
        emit bytesReceived(recvData);
#if 0
        qDebug() << "recv data len " << count;
        for(int i = 0;i < count;i++)
            qDebug("%c ",(quint8)(recvData.data())[i]);
#endif
    }
}
