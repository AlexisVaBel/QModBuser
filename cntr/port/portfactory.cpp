#include "portfactory.hpp"
#include "comportlnx.hpp"

#include <QDebug>

PortFactory::PortFactory(){
}

PortInterface *PortFactory::createPort(QString strPort){
    if(strPort.compare(QString("portlinux"),Qt::CaseInsensitive)==0){
        return new COMPortLnx();
        qDebug()<<"created linux port";
    }

    return NULL;
}
