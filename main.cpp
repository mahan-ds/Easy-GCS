#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include "serialhandler.h"
#include "serialhandleradaptor.h"
#include "mavlinkparser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SerialHandler *serialHandler = new SerialHandler;
    SerialHandlerAdaptor *serialAdaptor = new SerialHandlerAdaptor(serialHandler);
    QThread *serialThread = new QThread;
    mavlinkparser *mavlinkParser = new mavlinkparser;


    serialHandler->moveToThread(serialThread);


    engine.rootContext()->setContextProperty("serialHandler", serialHandler);
    engine.rootContext()->setContextProperty("serialAdaptor", serialAdaptor);

    QObject::connect(serialHandler, &SerialHandler::mavlinkMessageReceived,
                     mavlinkParser, &mavlinkparser::parseMavlinkMessage);

    QObject::connect(&app, &QGuiApplication::aboutToQuit, [&]() {
        qDebug() << "[INFO] Application exiting. Cleaning up threads...";
        serialThread->quit();
        serialThread->wait();
        serialHandler->deleteLater();
        serialThread->deleteLater();
    });

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
