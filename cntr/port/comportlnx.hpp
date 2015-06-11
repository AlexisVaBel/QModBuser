#ifndef COMPORTLNX_HPP
#define COMPORTLNX_HPP
#include <QObject>
#include "portinterface.hpp"
#include "cmn/serialparams.hpp"
#include <string>
#include <list>

static const int         COMERRCNT=5;
static const char    *COMErrs[COMERRCNT]={"","","","","Undefined"};
static const char    *COMDIR="/dev";


void signal_handler_IO(int status);

class COMPortLnx : public PortInterface{
public:
    COMPortLnx();
    ~COMPortLnx();
    // PortInterface interface
public:
    bool openPort(void *arg);
    bool closePort();
    bool readPort(char *chPack, int iCnt);
    bool writePort(char *chPack, int iCnt);
    void *getPrmPort(void *arg);
    void *getAllPorts();
    void *getPortErr();
    void *getPortType();

private:
    int                   m_iPortID;
    int                   m_iErr;
    bool                m_bConnected;
    SerialParams m_prms;
    std::list<std::string> m_lstPorts;
    std::string      m_sPort;

    bool                setPrmsPort(SerialParams prm);
    bool                setPrmsPort(int iBaud,int iDataBits, int iStopBits, int iFlow);
    bool                isItPort(const char *chName);
    std::list<std::string> getPorts();

};



#endif // COMPORTLNX_HPP
