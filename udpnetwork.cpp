#include "udpnetwork.h"

UdpNetwork::UdpNetwork()
{
}

UdpNetwork::~UdpNetwork()
{
    m_pUdpSocket->close();
    m_pUdpSocket->deleteLater();
}

void UdpNetwork::run()
{
    m_pUdpSocket = new QUdpSocket();
    m_pUdpSocket->bind(7000);
    connect(m_pUdpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()),Qt::DirectConnection);
    connect(m_pUdpSocket,SIGNAL(destroyed()),m_pUdpSocket,SLOT(deleteLater()),Qt::DirectConnection);
    qDebug()<<"NetWork start OK";
    exec();
}

void UdpNetwork::readMessages()
{
    char tmpBuff[4096];
    QHostAddress host;
    quint16 port;
    int c = m_pUdpSocket->readDatagram(tmpBuff, 4096, &host, &port);
    qDebug()<<__FUNCTION__<<"count:"<<c<<"IP:"<<host.toString()<<"Port:"<<port;
    emit toCfgFreqSignal(tmpBuff,host,port);

}

void UdpNetwork::sendMessages(QByteArray &byteArray, QHostAddress &address, quint16 port)
{
    int c = m_pUdpSocket->writeDatagram(byteArray, address, port);
    qDebug()<<__FUNCTION__<<"Len:"<<c;
}
