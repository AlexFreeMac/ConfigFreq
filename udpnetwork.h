#ifndef UDPNETWORK_H
#define UDPNETWORK_H
#include "QThread"
#include "QUdpSocket"
#include "QObject"
class UdpNetwork:public QThread
{
    Q_OBJECT
public:
    UdpNetwork();
    ~UdpNetwork();
protected:
    void run();
signals:
    void toCfgFreqSignal(char*, QHostAddress ,quint16);
public slots:
    void readMessages();
    void sendMessages(QByteArray &byteArray, QHostAddress &address, quint16 port);
private:
    QUdpSocket *m_pUdpSocket;
};

#endif // UDPNETWORK_H
