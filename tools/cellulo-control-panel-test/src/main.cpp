#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtBluetooth>
#include <QQuickWindow>
#include <QQmlContext>
#include "paper.h"

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Paper *paper = new Paper();

    engine.rootContext()->setContextProperty("paper", paper);

    engine.load(QUrl(QStringLiteral("qrc:///src/main.qml")));

    QQuickWindow *wnd1 = engine.rootObjects()[0]->findChild<QQuickWindow *>("controls window");
        if(wnd1)
            wnd1->setTitle("Control panel");
    QQuickWindow *wnd2 = engine.rootObjects()[0]->findChild<QQuickWindow *>("robot display window");
        if(wnd2)
            wnd2->setTitle("Display");
    wnd1->show();
    wnd2->show();

    return app.exec();
}
