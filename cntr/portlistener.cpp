#include "portlistener.hpp"
#include <QDebug>

PortListener::PortListener(QObject *parent) :
    QObject(parent),m_port(0),m_bStop(false){
}

void PortListener::setPort(PortInterface *port){
    m_port  =port;
    m_bStop=false;
}

void PortListener::process(){
    if(m_port!=0){
        char chByteArr[BUFFERINSZ]={0};
        char *chByte=chByteArr;
        while(!m_bStop){
            if(m_port->readPort(chByte,1)){
                emit byteReceived(chByte);
            }
            usleep(LISTENERSLEEP);
        }
    }
    emit finishedProcs();
}

void PortListener::stopProcs(){
    m_bStop=true;
}
