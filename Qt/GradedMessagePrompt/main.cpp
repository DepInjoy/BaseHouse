#include <QApplication>
#include "mainwindow.h"
#include "Bubble.h"
#include "TCPServer.h"
#include "TCPLink.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Bubble unit test
    Bubble b1;
    b1.showInfo(QString("Hello 1"));
    b1.showWarn(QString("WARNING 2"));
    b1.showWarn(QString("WARNING 3 WARNING 3"));
    b1.showError(QString("ERROR 4"));
    b1.showInfo(QString("ERROR 5"));

    //TCP unit test
    TCPServer* server = new TCPServer();
    TCPLink*   link = new TCPLink();
    QByteArray bytes("Hello World !");
    link->writeBytes(bytes);

    int exit = a.exec();

    if(!exit){
        //Recycle resources
        delete link;
        delete server;
    }
    return exit;
}
