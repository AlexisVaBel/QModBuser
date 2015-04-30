#include "comport.hpp"
#include <termios.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/types.h>

#include <QDebug>

COMPort::COMPort(){
    m_bConnected=false;
}

bool COMPort::openPort(void *arg){    
    closePort();
    SerialParams *lnkPrm=reinterpret_cast<SerialParams*>(arg);
    if(lnkPrm==0){
        // emit err;
        return false;
    };
    m_prms=*lnkPrm;
    int fd;
    std::string strFile=std::string(COMDIR)+std::string("/")+m_prms.strPort;
    m_iPortID=open(strFile.c_str(),O_RDWR|O_NOCTTY|O_NDELAY);
//    m_iPortID=open(strFile.c_str(),O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
    qDebug()<<"connect to "<<strFile.c_str()<<m_iPortID;
    fd=isatty(m_iPortID);
    if(fd!=1){
	closePort();
	return false;
    }
    if (!setPrmsPort(m_prms)) {
        // set prm error
        qDebug()<<"Not seted params";
        return false;
    }
    qDebug()<<"opend";
    m_bConnected=true;
    return true;
}

bool COMPort::closePort(){    
    close(m_iPortID);
    m_bConnected=false;
    return true;
}

bool COMPort::readPort(char *chPack, int iCnt){    
    int iVal=(read(m_iPortID,chPack,iCnt));
    if(iVal<0){
//        qDebug()<<iVal<<chPack<<"port "<<m_iPortID;
    }
    return(iVal>0);
}

bool COMPort::writePort(char *chPack, int iCnt){
    tcflush(m_iPortID,TCIOFLUSH);
    return (write(m_iPortID,chPack,iCnt)>0);
}

void *COMPort::getPortErr(){
    if((m_iErr>=COMERRCNT)||(m_iErr<0))return &COMErrs[COMERRCNT-1];
    else
    return &COMErrs[m_iErr];
}

bool COMPort::setPrmsPort(SerialParams prm){
    return setPrmsPort(prm.iBaudRate,prm.iDataBits,prm.iStopBits,prm.iFlowCnt);
}

bool COMPort::setPrmsPort(int iBaud, int iDataBits, int iStopBits, int iFlow){
    int iSucs=0;
    struct termios newtio;
    tcgetattr(m_iPortID, &newtio);
// clear old conf
    newtio.c_cflag&=~(CS5|CS6|CS7|CS8);
    newtio.c_cflag&=~(PARENB|PARODD);
    newtio.c_cflag&=~CSTOPB;
    // setting read write paramters
    newtio.c_lflag &=~OPOST;          // - �� ��������� ��������� ������
    newtio.c_lflag &=~ECHO;           // - ��������� ���-����� ��������� ��������
    newtio.c_lflag &=~ECHOE;        //  ��������� �������� ���������� ������� � ������
    // (���� ��������� � ������� ������������ �����, �� ������������ �������� ����. �������)
    newtio.c_lflag &=~ISIG;              // - ��������� ��������� ��������, ��� ������ ��������.
    newtio.c_lflag &=~ICANON;      // - ��������� ������������ ����� (������ ������ ��-���������)
// clear old conf
    cfsetispeed(&newtio,iBaud);
    cfsetospeed(&newtio,iBaud);
    newtio.c_cflag|=iDataBits;
    newtio.c_cflag|=iStopBits;
    newtio.c_cflag|=iFlow;
// with handler symbols
//    struct sigaction saio;
//    saio.sa_handler=signal_handler_IO;
//    saio.sa_flags=0;
//    saio.sa_restorer=NULL;
//    sigaction(SIGIO,&saio,NULL);
//    fcntl(m_iPortID,F_SETOWN,getpid()); //  allow process to receive SIGIO
//    fcntl(m_iPortID,F_SETFL,FASYNC);   // make procs async
// with handler symbols
    newtio.c_lflag             |=  CLOCAL;                // ������������ ������ ��������� ������
    newtio.c_lflag             |=  CREAD;                   //  ��������� �����
    newtio.c_cc[VMIN]   =1;
    newtio.c_cc[VTIME] =1;
    tcflush(m_iPortID,TCIOFLUSH);
    iSucs=tcsetattr(m_iPortID,TCSANOW,&newtio);           // ��������� ������    
    return (iSucs==0);
}

std::list<std::string> COMPort::getPorts(){
    DIR *dir;
    struct dirent *dp;
    std::string strFile;
    std::list<std::string> lstPorts;
    dir=opendir(COMDIR);
    if(dir==0)return lstPorts;
    while((dp=readdir(dir))!=NULL){
        if(sizeof(dp->d_name)>3){
            if((dp->d_name[0]=='t')&&(dp->d_name[1]=='t')&&(dp->d_name[2]=='y')){
                strFile=std::string(COMDIR)+std::string("/")+std::string(dp->d_name);
                if(isItPort(strFile.c_str()))lstPorts.push_front(dp->d_name);
            }
        }
    }
    closedir(dir);
    return lstPorts;
}

bool COMPort::isItPort(const char *chName){
    int fd=-1;
    bool bResult=false;
    fd=open(chName,O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd!=-1){
        if(isatty(fd))bResult=true;
    }
    close(fd);
    return bResult;
}


void *COMPort::getAllPorts(){
    m_lstPorts.clear();
    m_lstPorts=getPorts();
    return &m_lstPorts;
}


void *COMPort::getPrmPort(void *arg){    
    char *chName=reinterpret_cast<char*>(arg);
    if (chName==0)return 0;
    qDebug()<<chName;
    int fd=-1;
    std::string strFile=std::string(COMDIR)+std::string("/")+std::string(chName);    
    fd=open(strFile.c_str(),O_RDWR|O_NOCTTY|O_NDELAY);
    if(fd==-1)return 0;    
    struct termios oldtio;
    tcgetattr(m_iPortID, &oldtio);
    m_prms.iBaudRate= cfgetospeed(&oldtio);
    m_prms.iDataBits=(oldtio.c_cflag)&CSIZE;
    m_prms.iStopBits=(oldtio.c_cflag)&CSTOPB;
    m_prms.iFlowCnt=(oldtio.c_cflag)&(PARENB|PARODD);
    close(fd);
    return &m_prms;
}


void signal_handler_IO(int status){
    qDebug()<<"received something"<<status;
}