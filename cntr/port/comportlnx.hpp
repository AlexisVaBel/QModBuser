#ifndef COMPORTLNX_HPP
#define COMPORTLNX_HPP
#include "portinterface.hpp"
#include "cmn/serialparams.hpp"
#include <string>
#include <list>

static const int         COMERRCNT=5;
static const char    *COMErrs[COMERRCNT]={"","","","","Undefined"};
static const char    *COMDIR="/dev";


void signal_handler_IO(int status);

class COMPortLnx : public PortInterface
{
public:
    COMPortLnx();

    // PortInterface interface
public:
    bool openPort(void *arg);
    bool closePort();
    bool readPort(char *chPack, int iCnt);
    bool writePort(char *chPack, int iCnt);
    void *getPrmPort(void *arg);
    void *getAllPorts();
    void *getPortErr();

private:
    int                   m_iPortID;
    int                   m_iErr;
    bool                m_bConnected;
    SerialParams m_prms;
    std::list<std::string> m_lstPorts;

    bool                setPrmsPort(SerialParams prm);
    bool                setPrmsPort(int iBaud,int iDataBits, int iStopBits, int iFlow);
    bool                isItPort(const char *chName);
    std::list<std::string> getPorts();
};

#endif // COMPORTLNX_HPP
