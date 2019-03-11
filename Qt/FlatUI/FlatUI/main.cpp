#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <future>
#include "MainApplication.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    MainApplication* _mainApp = new MainApplication();
    std::shared_ptr<MainApplication> mainAppPtr(_mainApp);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/qml");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
