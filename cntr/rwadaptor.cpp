#include "rwadaptor.hpp"
#include <termios.h>
#include <QThread>
#include <assert.h>

RWAdaptor::RWAdaptor(QObject *obj):
QObject(obj){
}


void RWAdaptor::setPorts( PortInterface *port){
    m_port          =port;        
    assert(m_port!=NULL);
}

bool RWAdaptor::startListenPort(SerialParams prm){
    assert(m_port!=NULL);
    if(!m_port->openPort(&prm)){
        return false;
    };
    m_listener     =new PortListener();
    m_listener->setPort(m_port);
    QThread *thr=new QThread(this);
    m_listener->moveToThread(thr);
    connect(thr,SIGNAL(started()),m_listener,SLOT(process()));
    connect(m_listener,SIGNAL(byteReceived(char*)),this,SLOT(getPortByte(char*)));
    connect(m_listener,SIGNAL(finishedProcs()),thr,SLOT(quit()));
    thr->start();
    return true;
}

void RWAdaptor::stopListenPort(){
    if(m_listener!=0){
        m_listener->stopProcs();
    }
    if(m_port!=0){
        m_port->closePort();
    }
}

QStringList     RWAdaptor::getPorts(){
    QStringList strLst;
    std::list<std::string> *lstPnt, lst;
    lstPnt=reinterpret_cast<std::list<std::string> *> (m_port->getAllPorts());
    lst=*lstPnt;
    for(std::list<std::string>::iterator itGo=lst.begin();itGo!=lst.end();itGo++){
        strLst.append(itGo->c_str());
    }
    return strLst;
}

SerialParams RWAdaptor::getPortPrms(QString strPort){
    SerialParams prm,*prmPnt;
    prm.iBaudRate=0;
    prm.iDataBits=0;
    prm.iStopBits=0;
    prm.iFlowCnt=0;
    char *ch=const_cast<char *>(strPort.toStdString().c_str());
    prmPnt=reinterpret_cast<SerialParams*> (m_port->getPrmPort(ch));
    if(prmPnt==0)return prm;
    prm=*prmPnt;        
    return prm;
}

void RWAdaptor::getPortByte(char *ch){
    assert(m_reader!=0);
    m_reader->gotData(ch,1);
}

void RWAdaptor::connectWriter(){
    assert(m_writer!=0);
    connect(m_writer,SIGNAL(sendDataOut(const char*,int)),this,SLOT(setPortData(const char*,int)));
}

void RWAdaptor::setPortData(const char *ch,int iCnt){
    char *chSend=const_cast<char*> (ch);
    m_port->writePort(chSend,iCnt);
}
