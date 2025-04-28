#include "mavlinkparser.h"
#include "common/mavlink.h"
#include "serialhandler.h"
#include<QDebug>

mavlinkparser::mavlinkparser(QObject *parent)
    : QObject{parent}
{
}

void mavlinkparser::parseMavlinkMessage(const QByteArray &data)
{

    mavlink_message_t msg;
    mavlink_status_t status;

    for (int i = 0; i < data.size(); ++i) {
        uint8_t byte = static_cast<uint8_t>(data[i]);

        if (mavlink_parse_char(MAVLINK_COMM_0, byte, &msg, &status)) {

            qDebug() << "[MavlinkParser] Parsed message ID:" << msg.msgid;

            switch (msg.msgid) {

            case MAVLINK_MSG_ID_HEARTBEAT: {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &heartbeat);
                break;
            }
            case MAVLINK_MSG_ID_SYS_STATUS: {
                mavlink_sys_status_t sysStatus;
                mavlink_msg_sys_status_decode(&msg, &sysStatus);
                break;
            }
            case MAVLINK_MSG_ID_ATTITUDE: {
                mavlink_attitude_t attitude;
                mavlink_msg_attitude_decode(&msg, &attitude);
                break;
            }
            case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
                mavlink_global_position_int_t position;
                mavlink_msg_global_position_int_decode(&msg, &position);
                break;
            }
            case MAVLINK_MSG_ID_GPS_RAW_INT:{
                mavlink_gps_raw_int_t satellite;
                mavlink_msg_gps_raw_int_decode(&msg, &satellite);
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
            case MAVLINK_MSG_ID_MISSION_CURRENT:{
                mavlink_mission_current_t missionCurrent;
                mavlink_msg_mission_current_decode(&msg,&missionCurrent);
                break;
            }
            case MAVLINK_MSG_ID_STATUSTEXT: {
                mavlink_statustext_t statusText;
                mavlink_msg_statustext_decode(&msg, &statusText);
                break;
            }
            default:

                break;
            }
        }
    }
}




