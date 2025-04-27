#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QObject>

class SerialHandler : public QObject
{
    Q_OBJECT
public:
    explicit SerialHandler(QObject *parent = nullptr);
    //Q_INVOKABLE void startScanning();
    //Q_INVOKABLE void disconnectFromPixhawk();

signals:
    void mavlinkMessageReceived(const QByteArray &data);
    void connectedToPixhawk(const QString &portName);
    void unintentionaldisconnect();

private slots:
    void tryNextPort();
    void readData();

public slots:
    void startScanning();
    void disconnectFromPixhawk();
    Q_INVOKABLE void requestStartScanning();

private:
    void handleSerialError(QSerialPort::SerialPortError error);
    void resetScan();

    QList<QSerialPortInfo> portList;
    int currentPortIndex;
    QSerialPort *serial = nullptr;
    QTimer *scanTimer = nullptr;
};

#endif
