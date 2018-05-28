#ifndef WORK_H
#define WORK_H

#include <QObject>
#include <cfgfreq.h>
#include <udpnetwork.h>
class Work : public QObject
{
    Q_OBJECT
public:
    explicit Work(QObject *parent = 0);

signals:

public slots:

private:
    CfgFreq* m_pCfgFreq;
    UdpNetwork * m_pUDPNetwork;
};

#endif // WORK_H
