
#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <CelluloTcpRelayServer.h>
#include <CelluloTcpRelayClient.h>
#include <CelluloLocalRelayServer.h>
#include <CelluloLocalRelayClient.h>

using namespace Cellulo;

int main(int argc, char* argv[]){
    QCoreApplication app(argc, argv);
    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:///src/main.qml")));
    CelluloLocalRelayServer server;
    server.setListening(true);

    return app.exec();
}
