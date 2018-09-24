#include <QApplication>
#include "mainwindow.h"
#include "Bubble.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Bubble b1;
    b1.showInfo(QString("Hello 1"));
    b1.showWarn(QString("WARNING 2"));
    b1.showWarn(QString("WARNING 3 WARNING 3"));
    b1.showError(QString("ERROR 4"));
    b1.showInfo(QString("ERROR 5"));

    return a.exec();
}
