#include "devfactory.hpp"

#include "../rw/devrw.hpp"
#include "../rw/devlistener.hpp"

DevFactory::DevFactory(){
}

DevBase *DevFactory::getDevice(int idDev){
//for example , listener`s id 1,
//active writer`s id 2 etc..
    switch(idDev){
    case 1: return new DevListener();
    case 2: return new DevRW();
    }
    return NULL;
}

