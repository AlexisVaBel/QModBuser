#include "devmodbus.hpp"
#include <QDebug>

DevModBus::DevModBus(QString strFile){
}

void DevModBus::cmdRead(QString str) const{
    qDebug()<<"read"<<str;
}

void DevModBus::cmdWrite(QString str) const{
    qDebug()<<"write"<<str;
}

void DevModBus::cmdProcs(QString str) const{
    qDebug()<<"procs"<<str;
}
