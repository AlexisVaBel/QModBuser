#ifndef DEVLISTENER_HPP
#define DEVLISTENER_HPP

#include <QObject>
#include "devbase.hpp"
class DevListener : public DevBase
{
    Q_OBJECT
public:
    explicit DevListener(QObject *parent = 0);


    // DevBase interface
public:
    void procsReceived();
};


#endif // DEVLISTENER_HPP
