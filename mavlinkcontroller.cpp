#include "mavlinkcontroller.h"
#include <QDebug>

mavlinkcontroller::mavlinkcontroller(QObject *parent)
    : QObject{parent}
{}

void mavlinkcontroller::handleMavlinkMessage(uint32_t msgid, const mavlink_message_t &msg)
{
    switch (msgid) {

    case MAVLINK_MSG_ID_HEARTBEAT: {
        mavlink_heartbeat_t heartbeat;
        mavlink_msg_heartbeat_decode(&msg, &heartbeat);
        emit heartbeatUpdated(QString::number(heartbeat.custom_mode));
        break;
    }

    case MAVLINK_MSG_ID_SYS_STATUS: {
        mavlink_sys_status_t sysStatus;
        mavlink_msg_sys_status_decode(&msg, &sysStatus);
        emit batteryUpdated(QString::number(sysStatus.voltage_battery));
        break;
    }

    case MAVLINK_MSG_ID_ATTITUDE: {
        mavlink_attitude_t attitude;
        mavlink_msg_attitude_decode(&msg, &attitude);
        emit attitudeUpdated(attitude.roll, attitude.pitch, attitude.yaw);
        break;
    }

    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
        mavlink_global_position_int_t pos;
        mavlink_msg_global_position_int_decode(&msg, &pos);
        emit gpsPositionUpdated(pos.lat / 1e7, pos.lon / 1e7, pos.alt / 1000.0);
        emit speedUpdated(QString::number(qAbs(pos.vx)/100.0, 'f', 2));
        emit altitudeUpdated(QString::number(pos.alt/1000.0));
        qDebug()<< pos.alt;
        break;
    }
    case MAVLINK_MSG_ID_GPS_RAW_INT:{
        mavlink_gps_raw_int_t satellite;
        mavlink_msg_gps_raw_int_decode(&msg, &satellite);
        emit satelliteNumberUpdated(QString::number(satellite.satellites_visible));
        break;
    }
    case MAVLINK_MSG_ID_MISSION_ACK:{
        mavlink_mission_ack_t missionAck;
        mavlink_msg_mission_ack_decode(&msg,&missionAck);

        break;
    }
    case MAVLINK_MSG_ID_MISSION_REQUEST:{
        mavlink_mission_request_t missionReq;
        mavlink_msg_mission_request_decode(&msg,&missionReq);

        break;
    }

    case MAVLINK_MSG_ID_STATUSTEXT: {
        mavlink_statustext_t statusText;
        mavlink_msg_statustext_decode(&msg, &statusText);
        QString text = QString::fromUtf8(reinterpret_cast<const char*>(statusText.text));
        emit statusTextReceived(text.trimmed(), statusText.severity);
        break;
    }

    default:
        break;
    }
}

