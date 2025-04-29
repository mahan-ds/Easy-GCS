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
        switch (heartbeat.custom_mode) {
        case 0:
            customMode = "Stabilize";
            break;
        case 1:
            customMode = "Acro";
            break;
        case 2:
            customMode = "AltHold";
            break;
        case 3:
            customMode = "Auto";
            break;
        case 4:
            customMode = "Guided";
            break;
        case 5:
            customMode = "Loiter";
            break;
        case 6:
            customMode = "RTL";
            break;
        case 7:
            customMode = "Circle";
            break;
        case 9:
            customMode = "Land";
            break;
        case 11:
            customMode = "Drift";
            break;
        case 13:
            customMode = "Sport";
            break;
        case 14:
            customMode = "Flip";
            break;
        case 15:
            customMode = "Autotune";
            break;
        case 16:
            customMode = "PosHold";
            break;
        case 17:
            customMode = "Brake";
            break;
        case 18:
            customMode = "Throw";
            break;
        case 19:
            customMode = "Avoid_ADSB";
            break;
        case 20:
            customMode = "Guided_NoGPS";
            break;
        case 21:
            customMode = "Smart_RTL";
            break;
        case 22:
            customMode = "FlowHold";
            break;
        case 23:
            customMode = "Follow";
            break;
        case 24:
            customMode = "ZigZag";
            break;
        case 25:
            customMode = "SystemID";
            break;
        case 26:
            customMode = "Auto_RTL";
            break;
        case 27:
            customMode = "Auto_Landing_Gear";
            break;
        default:
            customMode = "Unknown";
            break;
        }
        emit heartbeatUpdated(customMode);
        break;
    }

    case MAVLINK_MSG_ID_SYS_STATUS: {
        mavlink_sys_status_t sysStatus;
        mavlink_msg_sys_status_decode(&msg, &sysStatus);

        float batteryVoltage = sysStatus.voltage_battery / 1000.0f; // میلی ولت → ولت
        emit batteryUpdated(QString::number(batteryVoltage, 'f', 1)); // مثلا 11.50
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
        emit speedUpdated(QString::number(qAbs(pos.vx)/100.0, 'f', 1));
        emit altitudeUpdated(QString::number(pos.relative_alt / 1000.0, 'f', 1));
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

