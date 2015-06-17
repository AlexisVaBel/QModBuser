#ifndef DEVBASE_HPP
#define DEVBASE_HPP

#include <QObject>
#include "./port/portinterface.hpp"

static const int LISTENERSLEEP=20000; // 20 msec
static const int BUFFERINSZ      =255;

class DevBase : public QObject
{
    Q_OBJECT
public:
    explicit DevBase(QObject *parent = 0);
    virtual void    setPort(PortInterface *port){m_port=port;}
    virtual void    stopProcs();
    virtual void    procsReceived()=0;
    void                sendBytes(char * chByte,int iCnt);
signals:
    void                byteReceived(char * chByte);
    void                finishedProcs();
public slots:
    virtual void    process();
protected:
    bool                    m_bStop;
    bool                    m_bSend;
    PortInterface   *m_port;
};

#endif // DEVBASE_HPP

