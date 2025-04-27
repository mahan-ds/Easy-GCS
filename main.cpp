#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include "serialhandler.h"
#include "serialhandleradaptor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SerialHandler *serialHandler = new SerialHandler;
    QThread *serialThread = new QThread;

    serialHandler->moveToThread(serialThread);

    //QObject::connect(serialThread, &QThread::started, serialHandler, &SerialHandler::startScanning);

    SerialHandlerAdaptor *serialAdaptor = new SerialHandlerAdaptor(serialHandler);

    engine.rootContext()->setContextProperty("serialHandler", serialHandler);
    engine.rootContext()->setContextProperty("serialAdaptor", serialAdaptor);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    engine.loadFromModule("EasyGCS", "Main");
    serialThread->start();
    return app.exec();
}
