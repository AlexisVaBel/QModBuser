#ifndef DEVICEINTERFACE_HPP
#define DEVICEINTERFACE_HPP

#include <QString>

class DeviceInterface{
public:
    DeviceInterface(QString name="none",QString cmd="no"):
    m_sName(name),
    m_sCmd(cmd){}
    virtual QString getName()   {return m_sName ;}
    virtual QString getCmd()    {return m_sCmd   ;}
    virtual QString getAnswer(){return m_sAnsw  ;}

    virtual void setName(QString sname)     {m_sName=sname ;}
    virtual void setCmd(QString scmd)         {m_sCmd=scmd   ;}
    virtual void setAnswer(QString sanswer){m_sAnsw=sanswer  ;}

protected:
    QString m_sName;
    QString m_sCmd;
    QString m_sAnsw;
};

#endif // DEVICEINTERFACE_HPP
