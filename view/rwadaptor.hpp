#ifndef VIEWPORTADAPTOR_HPP
#define VIEWPORTADAPTOR_HPP

#include <QObject>
#include "../view/consoleview.hpp"
#include "../cntr/portlistener.hpp"
#include "../cntr/port/portinterface.hpp"
#include "./cntr/port/cmn/serialparams.hpp"

class ViewPortAdaptor:public QObject{
Q_OBJECT
public:
    ViewPortAdaptor(QObject *obj);
    void    setViews(ConsoleView *in,ConsoleView *out);
    void    setPorts  (PortInterface *port);
    void    viewsSlots();
public slots:
    void                 setPortData(const char *ch, int iCnt);
    bool                 startListenPort(SerialParams prm);
    void                 stopListenPort();
    SerialParams getPortPrms(QString strPort);
    QStringList    getPorts();
    void                 getPortByte(char *ch);
private:
    ConsoleView     *m_viewIn;
    ConsoleView     *m_viewOut;    
    PortInterface    *m_port;
    PortListener     *m_listener;
};

#endif // VIEWPORTADAPTOR_HPP
