#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <cfgfreq.h>
#include <udpnetwork.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CfgFreq* m_pCfgFreq;
    UdpNetwork * m_pUDPNetwork;
};

#endif // WIDGET_H
