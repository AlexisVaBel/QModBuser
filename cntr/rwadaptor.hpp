#ifndef RWPORTADAPTOR_HPP
#define RWPORTADAPTOR_HPP

#include <QObject>
#include <QStringList>
#include "../cmn/serialparams.hpp"
#include "../port/portinterface.hpp"
#include "../rw/devbase.hpp"
#include "../rw/rwprovider.hpp"

class RWAdaptor:public QObject{
Q_OBJECT
public:
    RWAdaptor(QObject *obj);    
    void    setPort  (PortInterface *port);
    void    setReader(RWProvider *reader){m_reader=reader;}
    void    setWriter(RWProvider *writer){m_writer=writer;connectWriter();}

public slots:
    void                 setPortData(const char *ch, int iCnt);
    bool                 startListenPort(SerialParams prm);
    void                 stopListenPort();
    SerialParams getPortPrms(QString strPort);
    QStringList    getPorts();
    void                 getPortByte(char *ch);
private:    
    RWProvider     *m_reader;
    RWProvider     *m_writer;

    PortInterface    *m_port;
    DevBase            *m_device;
    void                    connectWriter();
};

#endif // RWPORTADAPTOR_HPP
