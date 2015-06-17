#include "rwprovider.hpp"

RWProvider::RWProvider(QObject *obj){

}

RWProvider::~RWProvider(){

}

void RWProvider::gotData(const char *ch, int iCnt){
    emit sendDataOut(ch,iCnt);
}

