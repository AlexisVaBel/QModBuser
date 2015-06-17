#ifndef SERIALPARAMS_HPP
#define SERIALPARAMS_HPP
#include <string>
struct SerialParams{
    std::string strPort;
    int              iBaudRate;
    int              iDataBits;
    int              iStopBits;
    int              iFlowCnt;
};
#endif // SERIALPARAMS_HPP
