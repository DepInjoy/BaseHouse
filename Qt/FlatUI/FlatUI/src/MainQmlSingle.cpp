#include <QDebug>
#include "MainQmlSingle.h"

MainQmlSingle::MainQmlSingle(MainApplication* app)
{
    Q_UNUSED(app)
}

MainQmlSingle::~MainQmlSingle()
{
    qDebug() << "delete MainQmlSingle";
}
