#ifndef PORTINTERFACE_HPP
#define PORTINTERFACE_HPP
class PortInterface{
public:
    virtual void *getPortType()=0;
    virtual bool openPort(void *arg)=0;
    virtual bool closePort()=0;
    virtual bool readPort(char *chPack,int iCnt)=0;
    virtual bool writePort(char* chPack,int iCnt)=0;
    virtual void *getPrmPort(void *arg)=0;
    virtual void *getAllPorts()=0;
    virtual void *getPortErr()=0;
    virtual ~PortInterface(){}
};
#endif // PORTINTERFACE_HPP
