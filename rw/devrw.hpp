#ifndef DEVRW_H
#define DEVRW_H
#include "devbase.hpp"

class DevRW:public DevBase
{
public:
    DevRW();    
    // DevBase interface
public:
    void procsReceived();
};

#endif // DEVRW_H
