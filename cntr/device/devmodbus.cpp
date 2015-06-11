#include "devmodbus.hpp"

DevModBus::DevModBus(DeviceInterface *device):
CmdInterface(device){
}

QString DevModBus::getName(){
    if(this->m_iDev!=NULL)
        return this->m_iDev->getName()+":"+this->m_sName;
    else
        return this->m_sName;
}

QString DevModBus::getCmd(){
    if(this->m_iDev!=NULL)
        return this->m_iDev->getCmd()+this->m_sCmd;
    else
        return this->m_sCmd;
}

QString DevModBus::getAnswer(){
    if(this->m_iDev!=NULL)
        return this->m_iDev->getAnswer()+this->m_sAnsw;
    else
        return this->m_sAnsw;
}

void DevModBus::setName(QString sname){
    m_sName=sname;
}

void DevModBus::setCmd(QString scmd){
    m_sCmd=scmd;
}

void DevModBus::setAnswer(QString sanswer){
    m_sAnsw=sanswer;
}
