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
     void requestDataStream(uint8_t stream_id, uint16_t rate, bool start);

public:
    void handleSerialError(QSerialPort::SerialPortError error);
    void resetScan();

    QList<QSerialPortInfo> portList;
    int currentPortIndex;
    QSerialPort *serial = nullptr;
    QTimer *scanTimer = nullptr;
private:
    bool pixhawkConnected = false;
};

#endif
