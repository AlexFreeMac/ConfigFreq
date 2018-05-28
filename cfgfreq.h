#ifndef CFGFREQ_H
#define CFGFREQ_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include "QCoreApplication"
#include <QString>
#include <QSettings>
#include <QDebug>
#include <QHostAddress>
typedef struct QueryFreqData
{
    int tx1;
    int rx1;
    int tx2;
    int rx2;
    int tx3;
    int rx3;
    int time;
}QueryFreqData;
class CfgFreq : public QObject
{
    Q_OBJECT
public:
    explicit CfgFreq(QObject *parent = 0);
    ~CfgFreq();
signals:
    void sendFreqSignal(QByteArray &, QHostAddress &,quint16 );
public slots:
    void dealQuery(char*data, QHostAddress address,quint16 port);
private:
    QJsonDocument json;
    QJsonArray jsonArray;
    QueryFreqData *m_pQueryFreqData;
    int dataCount;
    QueryFreqData findFreq(int time);
};

#endif // CFGFREQ_H
