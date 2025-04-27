#include "serialhandleradaptor.h"

SerialHandlerAdaptor::SerialHandlerAdaptor(SerialHandler *handler, QObject *parent)
    : QObject(parent), serialHandler(handler)
{
    connect(serialHandler, &SerialHandler::connectedToPixhawk,
            this, &SerialHandlerAdaptor::connectedToPixhawk);

    connect(serialHandler, &SerialHandler::unintentionaldisconnect,
            this, &SerialHandlerAdaptor::unintentionaldisconnect);
}
