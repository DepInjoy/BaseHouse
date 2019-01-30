#include "UDPClient.h"
#include <QAbstractSocket>

UDPClient::UDPClient():
    _udpClient(NULL)
    , _hostAddr("127.0.0.1")
    , _port(6000)
{
    _udpClient = new QUdpSocket();
    if(!_udpClient->bind(QHostAddress(_hostAddr),_port,
            QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        qDebug() << "Error: bind addr " << _hostAddr << " port " << _port << "failed !";
    }
    connect(_udpClient,&QUdpSocket::readyRead,this,&UDPClient::_received);
}
UDPClient::~UDPClient()
{
    if(_udpClient){
        _udpClient->close();
        _udpClient->deleteLater();
        _udpClient = NULL;
    }
}

void UDPClient::writeBytes(QByteArray& bytes,QHostAddress hostAddr,quint16 port)
{
    if(_udpClient){
        int len = _udpClient->writeDatagram(bytes,hostAddr,port);
        if(len < 0){
            qDebug() << "Error Client try to write " << bytes.data() << "failed !" ;
        }
    }
}

void UDPClient::setHost(const QString addr,const quint16 port)
{
    if(_hostAddr != QHostAddress(addr) || _port != port){
        _hostAddr = addr;
        _port = port;
        if(!_udpClient->bind(QHostAddress(_hostAddr),_port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
            qDebug() << "Error: Client bind addr " << _hostAddr << " port " << _port << "failed !";
        }
        connect(_udpClient,&QUdpSocket::readyRead,this,&UDPClient::_received);
    }
}

void UDPClient::_received()
{
    QByteArray bytes;
    QHostAddress chost;
    quint16 cport;
    while (_udpClient->hasPendingDatagrams()) {
        bytes.resize(_udpClient->pendingDatagramSize());
        _udpClient->readDatagram(bytes.data(),bytes.size(),&chost,&cport);
#if 0
        qDebug() << "Client size " << bytes.size() << " data " << bytes.data()
                 << " host " << chost << " port " << cport;
#endif
        emit recvBytes(bytes);
    }
}


