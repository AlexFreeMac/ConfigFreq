#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pUDPNetwork = new UdpNetwork();
    m_pUDPNetwork->start();
    m_pCfgFreq = new CfgFreq();
    connect(m_pUDPNetwork,SIGNAL(toCfgFreqSignal(char*,QHostAddress,quint16)),
            m_pCfgFreq,SLOT(dealQuery(char*,QHostAddress,quint16)),Qt::DirectConnection);
    connect(m_pCfgFreq,SIGNAL(sendFreqSignal(QByteArray &, QHostAddress &,quint16 )),
            m_pUDPNetwork,SLOT(sendMessages(QByteArray &, QHostAddress &,quint16 )),Qt::DirectConnection);
}


Widget::~Widget()
{
    delete ui;
}
