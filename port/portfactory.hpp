#ifndef PORTFACTORY_HPP
#define PORTFACTORY_HPP

#include <QString>
#include "./portinterface.hpp"
class PortFactory
{
public:
    PortFactory();
    PortInterface *createPort(QString strPort);
};

#endif // PORTFACTORY_HPP
