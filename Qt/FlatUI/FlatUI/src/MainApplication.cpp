#include <QtQml>
#include <functional>
#include "MainApplication.h"
#include "MainQmlSingle.h"
#include "Palette.h"

static QObject* MainQmlSingleApplication(QQmlEngine *,QJSEngine *);
static MainApplication* mainApp()
{
    return _app;
}

static QObject* MainQmlSingleApplication(QQmlEngine *,QJSEngine *)
{
    MainQmlSingle* qmlSingle = new MainQmlSingle(mainApp());
    return qmlSingle;
}

MainApplication::MainApplication(QObject *parent) : QObject(parent)
{
    _app = this;
    _init();
}

MainApplication::~MainApplication()
{
    qDebug() << "delete MainApplication";
}

void MainApplication::_init(void)
{
    qmlRegisterSingletonType<MainQmlSingle>("FlatUI",           1,      0,      "FlatUI",   MainQmlSingleApplication);
    qmlRegisterType<Palette>                ("FlatUI.Palette",  1,      0,      "Palette");
}
