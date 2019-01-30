#include "UDPServer.h"

UDPServer::UDPServer():
    _udpsocket(NULL)
    , _address("127.0.0.1")
    , _port(6000)
{
    qRegisterMetaType<UDPServer*>("UDPServer");
    moveToThread(this);
    start(HighPriority);
}

void UDPServer::run()
{
    _udpsocket = new QUdpSocket(this);
    if(!_udpsocket->bind(QHostAddress(_address), _port,
            QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        qDebug() << "Error Server try to bind address " << _address
                 << "port " << _port << "to UDPSocket failed !";
    }
    connect(_udpsocket,&QUdpSocket::readyRead,this,&UDPServer::_received);
    connect(this,   &UDPServer::_writeToHostSingal,this,    &UDPServer::_writeToHostSlot);
    exec();
}

UDPServer::~UDPServer()
{
    if(_udpsocket){
        _udpsocket->close();
        _udpsocket->deleteLater();
        _udpsocket = NULL;
    }
    quit();
    wait();
}

void UDPServer::_received()
{
    QByteArray bytes;
    QHostAddress chost;
    quint16 cport;
    while (_udpsocket->hasPendingDatagrams()) {
        bytes.resize(_udpsocket->pendingDatagramSize());
        _udpsocket->readDatagram(bytes.data(),bytes.size(),&chost,&cport);
        qDebug() << "Server size " << bytes.size() << " data " << bytes.data()
                 << " host " << chost.toString() << " port " << cport;
        emit recvBytes(bytes,chost.toString(),cport);
    }
}
void UDPServer::_writeToHostSlot(const QByteArray& data, QString dstAddr, quint16 dstPort)
{
    if(!_udpsocket){
        qDebug() << "Error socket is not created";
        return;
    }

    int wlen =  _udpsocket->writeDatagram(data,QHostAddress(dstAddr),dstPort);
    if(wlen < 0){
        qDebug() << "Error: Server try write data: "<< data.data() << "to "
                 << dstAddr<< " port " << dstPort << "failed !";
        return;
    }
    return;
}

void UDPServer::writeToHost(QByteArray byte, QString dstAddr, quint16 port)
{
    emit _writeToHostSingal(byte,dstAddr,port);
}
