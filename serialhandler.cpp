#include "serialhandler.h"
#include "common/mavlink.h"
#include <QThread>
#include <QDebug>

SerialHandler::SerialHandler(QObject *parent)
    : QObject(parent), currentPortIndex(0)
{
    // connect(scanTimer, &QTimer::timeout, this, &SerialHandler::tryNextPort);
    // connect(serial, &QSerialPort::readyRead, this, &SerialHandler::readData);
    // connect(serial, &QSerialPort::errorOccurred, this, &SerialHandler::handleSerialError);

}

void SerialHandler::startScanning()
{
    qDebug() << "[INFO] Starting serial port scan in thread:" << QThread::currentThread();

    if (!scanTimer) {
        scanTimer = new QTimer(this);
        connect(scanTimer, &QTimer::timeout, this, &SerialHandler::tryNextPort);
    }

    if (!serial) {
        serial = new QSerialPort();
        connect(serial, &QSerialPort::readyRead, this, &SerialHandler::readData);
        connect(serial, &QSerialPort::errorOccurred, this, &SerialHandler::handleSerialError);
    }

    portList = QSerialPortInfo::availablePorts();
    currentPortIndex = 0;
    scanTimer->start(1000);

}

void SerialHandler::disconnectFromPixhawk()
{
    qDebug() << "[INFO] Manually disconnecting from Pixhawk...";
    scanTimer->stop();
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "[INFO] Serial port closed.";
    }
}

void SerialHandler::tryNextPort()
{
    if (currentPortIndex >= portList.size()) {
        qDebug() << "[INFO] No valid MAVLink found. Restarting scan.";
        resetScan();
        return;
    }

    const QSerialPortInfo &info = portList[currentPortIndex++];
    serial->close();
    serial->setPort(info);
    serial->setBaudRate(QSerialPort::Baud115200); // Change if needed

    if (serial->open(QIODevice::ReadOnly)) {
        qDebug() << "[INFO] Testing port:" << info.portName();
    } else {
        qDebug() << "[WARNING] Failed to open port:" << info.portName();
    }
}

void SerialHandler::readData()
{
    QByteArray data = serial->readAll();
    if (data.isEmpty())
        return;

    unsigned char header = static_cast<unsigned char>(data[0]);
    if (header == 0xFE || header == 0xFD) {
        qDebug() << "[SUCCESS] MAVLink message received on port:" << serial->portName();

        if (scanTimer && scanTimer->isActive()) {
            QMetaObject::invokeMethod(scanTimer, "stop", Qt::QueuedConnection);
        }

        emit connectedToPixhawk(serial->portName());
        emit mavlinkMessageReceived(data);
    } else {
        qDebug() << "[DEBUG] Non-MAVLink data received:" << data.toHex();
    }
}

void SerialHandler::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qDebug() << "[ERROR] Pixhawk disconnected. Attempting to reconnect...";
        serial->close();

        QTimer::singleShot(2000, this, [this]() {
            QMetaObject::invokeMethod(this, "startScanning", Qt::QueuedConnection);
        });

        emit unintentionaldisconnect();
    }
}


void SerialHandler::resetScan()
{
    portList = QSerialPortInfo::availablePorts();
    currentPortIndex = 0;
}

void SerialHandler::requestStartScanning()
{
    QMetaObject::invokeMethod(this, "startScanning", Qt::QueuedConnection);
}
