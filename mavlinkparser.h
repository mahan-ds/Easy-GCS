#ifndef MAVLINKPARSER_H
#define MAVLINKPARSER_H

#include <QObject>

class mavlinkparser : public QObject
{
    Q_OBJECT
public:
    explicit mavlinkparser(QObject *parent = nullptr);

signals:

public slots:
    void parseMavlinkMessage(const QByteArray &data);

public:

};

#endif // MAVLINKPARSER_H
