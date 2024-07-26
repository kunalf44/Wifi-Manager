#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<connection.h>
  #include <QQmlEngine>
#include <QQmlContext>
#include <QtWebEngineQuick>
#include<connection.h>

int main(int argc, char *argv[])
{

    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);
    // qmlRegisterType<Connection>("Kunal",1,0,"Con");
    Connection wifi;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("wifi",&wifi);
    const QUrl url(u"qrc:/delete_networksettings/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
