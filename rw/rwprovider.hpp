#ifndef RWPROVIDER_HPP
#define RWPROVIDER_HPP

#include <QObject>

class RWProvider :public QObject{
Q_OBJECT
public:
    RWProvider(QObject *obj);
    ~RWProvider();
    void    gotData(const char*ch, int iCnt);
signals:
    void    sendDataOut(const char*,int iCnt);
};
#endif // RWPROVIDER_HPP
