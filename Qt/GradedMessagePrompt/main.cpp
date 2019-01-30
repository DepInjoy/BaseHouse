#include <QApplication>
#include "mainwindow.h"
#include "Bubble.h"
#ifdef TCP_LOOP_TEST
#include "TCPServer.h"
#include "TCPLink.h"
#endif
#ifdef UDP_LOOP_TEST
#include "UDPClient.h"
#include "UDPServer.h"
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if BUBBLE_TEST
    //Bubble unit test
    Bubble b1;
    b1.showInfo(QString("Hello 1"));
    b1.showWarn(QString("WARNING 2"));
    b1.showWarn(QString("WARNING 3 WARNING 3"));
    b1.showError(QString("ERROR 4"));
    b1.showInfo(QString("ERROR 5"));
#endif
#ifdef TCP_LOOP_TEST
    //TCP unit test
    TCPServer* server = new TCPServer();
    TCPLink*   link = new TCPLink();
    QByteArray bytes("Hello World !");
    link->writeBytes(bytes);
#endif
#ifdef UDP_LOOP_TEST
    //UDP unit test
    UDPServer* udpServer = new UDPServer();
    UDPClient* udpClient = new UDPClient();
    udpClient->writeBytes(QByteArray("Hello World!"));
#endif
    int exit = a.exec();

    if(!exit){
        //Recycle resources
#ifdef TCP_LOOP_TEST
        delete link;
        delete server;
#endif
#ifdef UDP_LOOP_TEST
        delete udpServer;
        delete udpClient;
#endif
    }
    return exit;
}
