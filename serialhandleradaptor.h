#ifndef SERIALHANDLERADAPTOR_H
#define SERIALHANDLERADAPTOR_H

#include <QObject>
#include "serialhandler.h"

class SerialHandlerAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit SerialHandlerAdaptor(SerialHandler *handler, QObject *parent = nullptr);

signals:
    void connectedToPixhawk(const QString &portName);
    void unintentionaldisconnect();

private:
    SerialHandler *serialHandler;
};

#endif // SERIALHANDLERADAPTOR_H
