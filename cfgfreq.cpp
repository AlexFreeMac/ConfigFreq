#include "cfgfreq.h"
#include "QFile"
CfgFreq::CfgFreq(QObject *parent) :
    QObject(parent)
{
    QString dir = QCoreApplication::applicationDirPath();
    QString iniFilePath = dir+"/cfgfreq.ini";
    qDebug()<<"Current Dir:"<<iniFilePath;
    QFile file(iniFilePath);
    file.open(QIODevice::ReadOnly);
    QByteArray tmpbytearray;
    tmpbytearray = file.readAll();
    tmpbytearray = tmpbytearray.remove(0,19);
    QJsonParseError jsonError;
    json = QJsonDocument::fromJson(tmpbytearray, &jsonError);
    if(jsonError.error == QJsonParseError::NoError)
    {
        jsonArray = json.array();
        qDebug()<<"JsonCount:"<<jsonArray.count();
        dataCount = jsonArray.count();
        m_pQueryFreqData = new QueryFreqData[dataCount];
        for(int i = 0; i < dataCount;i++)
        {
//            jsonArray.at(i).object();
            QJsonObject rootobj = jsonArray.at(i).toObject();
            QString tx1 = rootobj.value("Tx1").toString();
            QString rx1 = rootobj.value("Rx1").toString();
            QString tx2 = rootobj.value("Tx2").toString();
            QString rx2 = rootobj.value("Rx2").toString();
            QString tx3 = rootobj.value("Tx3").toString();
            QString rx3 = rootobj.value("Rx3").toString();
            QString dt = rootobj.value("DtInt").toString();
            //qDebug()<<tx1.toInt()<<rx1.toInt()<<tx2.toInt()<<rx2.toInt()<<tx3.toInt()<<rx3.toInt()<<dt.toInt();
            m_pQueryFreqData[i].tx1 = tx1.toInt();
            m_pQueryFreqData[i].rx1 = rx1.toInt();
            m_pQueryFreqData[i].tx2 = tx2.toInt();
            m_pQueryFreqData[i].rx2 = rx2.toInt();
            m_pQueryFreqData[i].tx3 = tx3.toInt();
            m_pQueryFreqData[i].rx3 = rx3.toInt();
            m_pQueryFreqData[i].time = dt.toInt();
        }
        QueryFreqData tmpData = m_pQueryFreqData[0];
        for(int i = 0; i < dataCount-1; i++)
        {
            for(int j = 0; j < dataCount-1 -i; j++)
            {
                if (m_pQueryFreqData[j].time > m_pQueryFreqData[j + 1].time)
               {
                   tmpData = m_pQueryFreqData[j];
                   m_pQueryFreqData[j] = m_pQueryFreqData[j + 1];
                   m_pQueryFreqData[j + 1] = tmpData;
               }
            }
        }
        for(int i = 0; i < dataCount; i++)
        {
            qDebug()<<
                       m_pQueryFreqData[i].tx1 <<
                       m_pQueryFreqData[i].rx1 <<
                       m_pQueryFreqData[i].tx2 <<
                       m_pQueryFreqData[i].rx2 <<
                       m_pQueryFreqData[i].tx3 <<
                       m_pQueryFreqData[i].rx3 <<
                       m_pQueryFreqData[i].time;
        }
    }
    else
    {
        qDebug()<<"Json Format error";
    }
    file.close();
}

CfgFreq::~CfgFreq()
{
    delete[] m_pQueryFreqData;
}

void CfgFreq::dealQuery(char *data, QHostAddress address, quint16 port)
{
    QString strtime;
    strtime = strtime.fromLatin1(data);
    qDebug()<<"Time int"<<strtime<<strtime.toInt();
    QueryFreqData tmp = findFreq(strtime.toInt());
    char buff[sizeof(tmp)];
    memcpy(buff,(char*)&tmp,sizeof(tmp));

    QByteArray tmpByteArray;
    tmpByteArray = tmpByteArray.fromRawData(buff,sizeof(tmp));
    qDebug()<<"Buff size:"<<tmpByteArray.size();

    emit sendFreqSignal(tmpByteArray, address,port);
}

QueryFreqData CfgFreq::findFreq(int time)
{
    for(int i = 0 ; i < dataCount-1; i++)
    {
        if((time >= m_pQueryFreqData[i].time) && (time < m_pQueryFreqData[i+1].time))
        {
            qDebug()<<"find freq"<<m_pQueryFreqData[i].tx1<<m_pQueryFreqData[i].time;
            return m_pQueryFreqData[i];
        }
        else
        {
            if(i+1 == dataCount -1)
            {
                qDebug()<<"find freq"<<m_pQueryFreqData[i+1].tx1<<m_pQueryFreqData[i+1].time;
                return m_pQueryFreqData[i+1];
            }
        }
    }
    QueryFreqData tmp;
    memset(&tmp,0,sizeof(tmp));
    return tmp;
}
