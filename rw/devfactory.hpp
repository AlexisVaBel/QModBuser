#ifndef DEVFACTORY_H
#define DEVFACTORY_H

#include "../rw/devbase.hpp"

class DevFactory
{
public:
    DevFactory();
    static DevBase *getDevice(int idDev);
};

#endif // DEVFACTORY_H
