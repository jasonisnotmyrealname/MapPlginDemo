#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtPlugin>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    Q_IMPORT_PLUGIN(GeoServiceProviderFactory)

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();


}

