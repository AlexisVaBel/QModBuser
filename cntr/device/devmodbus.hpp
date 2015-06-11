#ifndef DEVMODBUS_HPP
#define DEVMODBUS_HPP
#include "cmdinterface.hpp"
#include "deviceinterface.hpp"
class DevModBus:public CmdInterface
{
public:
    DevModBus(DeviceInterface *device=NULL);
protected:


    // DeviceInterface interface
public:
    QString getName();
    QString getCmd();
    QString getAnswer();

    // DeviceInterface interface
public:
    void setName(QString sname);
    void setCmd(QString scmd);
    void setAnswer(QString sanswer);
};



#endif // DEVMODBUS_HPP
