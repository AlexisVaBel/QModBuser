#ifndef CMDINTERFACE_HPP
#define CMDINTERFACE_HPP
#include "deviceinterface.hpp"

class CmdInterface: public DeviceInterface{
public:
    CmdInterface(DeviceInterface *device):m_iDev(device){}
protected:
    DeviceInterface *m_iDev;
};


#endif // CMDINTERFACE_HPP
