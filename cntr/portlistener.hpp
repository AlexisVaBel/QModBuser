#ifndef PORTLISTENER_HPP
#define PORTLISTENER_HPP

#include <QObject>
#include "./port/portinterface.hpp"
static const int LISTENERSLEEP=25;
static const int BUFFERINSZ      =255;
class PortListener : public QObject
{
    Q_OBJECT
public:
    explicit PortListener(QObject *parent = 0);
    void    setPort(PortInterface *port);
    void    stopProcs();
signals:
    void    byteReceived(char * chByte);
    void    finishedProcs();
public slots:
    void    process();
private:
    bool                    m_bStop;
    PortInterface   *m_port;
};

#endif // PORTLISTENER_HPP
