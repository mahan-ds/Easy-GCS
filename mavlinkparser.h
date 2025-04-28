#ifndef MAVLINKPARSER_H
#define MAVLINKPARSER_H

#include <QObject>
#include "common/mavlink.h"

class mavlinkparser : public QObject
{
    Q_OBJECT
public:
    explicit mavlinkparser(QObject *parent = nullptr);

signals:
    void sendMavlinkMessage2Controller(uint32_t msgid, const mavlink_message_t &msg);

public slots:
    void parseMavlinkMessage(const QByteArray &data);

public:

};

#endif // MAVLINKPARSER_H
