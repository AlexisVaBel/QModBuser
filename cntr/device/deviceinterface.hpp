#ifndef DEVICEINTERFACE_HPP
#define DEVICEINTERFACE_HPP
#include <QString>

class DeviceInterface{
public:        
    virtual void    cmdRead(QString str)    const= 0;
    virtual void    cmdWrite(QString str)   const= 0;
    virtual void    cmdProcs(QString str)   const=0;

protected:
    bool     m_bRun;
};

#endif // DEVICEINTERFACE_HPP
