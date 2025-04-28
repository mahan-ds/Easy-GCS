#ifndef MAVLINKCONTROLLER_H
#define MAVLINKCONTROLLER_H

#include "common/mavlink.h"
#include <QObject>

class mavlinkcontroller : public QObject
{
    Q_OBJECT
public:
    explicit mavlinkcontroller(QObject *parent = nullptr);

public slots:
    void handleMavlinkMessage(uint32_t msgid, const mavlink_message_t &msg);

signals:
    void batteryUpdated(QString battery);
    void attitudeUpdated(float roll, float pitch, float yaw);
    void gpsPositionUpdated(double lat, double lon, double alt);
    void heartbeatUpdated(QString mode);
    void statusTextReceived(QString text, uint8_t severity);
    void satelliteNumberUpdated(QString satellite);
    void speedUpdated(QString speed);
    void altitudeUpdated(QString altitude);
};

#endif // MAVLINKCONTROLLER_H
