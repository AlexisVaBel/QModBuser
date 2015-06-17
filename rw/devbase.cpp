#include "devbase.hpp"

DevBase::DevBase(QObject *parent) : QObject(parent),m_port(0){
    m_bStop=false;
    m_bSend=false;
}

void DevBase::stopProcs(){
    m_bStop=true;
}

void DevBase::sendBytes(char *chByte, int iCnt){
    m_bSend=true;
    m_port->writePort(chByte,iCnt);
    m_bSend=false;
}

void DevBase::process(){
    if(m_port!=0){
        char chByteArr[BUFFERINSZ]={0};
        char *chByte=&chByteArr[0];
        while(!m_bStop){
            if(!m_bSend){
                if(m_port->readPort(chByte,1)){
                    emit byteReceived(chByte);
                }
            }
            usleep(LISTENERSLEEP);
        }
    }
    emit finishedProcs();
}

