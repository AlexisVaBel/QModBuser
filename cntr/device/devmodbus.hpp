#ifndef DEVMODBUS_HPP
#define DEVMODBUS_HPP
#include "deviceinterface.hpp"

#include <QString>

class DevModBus : public DeviceInterface{
public:
    DevModBus(QString strFile);


    // DeviceInterface interface
public:
    void cmdRead(QString str) const;
    void cmdWrite(QString str) const;
    void cmdProcs(QString str) const;
};

#endif // DEVMODBUS_HPP
