#include "charcoder.h"
#include <QTextCodec>
#include <QDebug>

CharCoder::CharCoder():
    m_iChPos(0){
}

CharCoder::~CharCoder(){
}

int CharCoder::encodToUTF8(QString strSend, char *chOut, int iChLng){
    int iPos=0;
    if(strSend.count()>=iChLng)  return iPos;
    while(iPos<strSend.count()){
        *(chOut)=strSend.at(iPos++).toLatin1();
        chOut++;
    };
    return iPos;
}

int CharCoder::encodToUTF16(QString strSend, char *chOut, int iChLng){
    uint uiVal=0, iPos=0;
    if((strSend.length()*2)>=iChLng)return iPos;
    iPos=strSend.length()*2;
    for(int i=0;i<strSend.length();i++){
        uiVal=strSend.at(i).unicode();
        chOut[i*2]     =uiVal>>8;
        chOut[i*2+1] =uiVal&0xFF;
    }
    return iPos;
}

int CharCoder::encodToHEX(QString strSend, char *chOut, int iChLng){
    bool ok=false;
    QString str="";
    int iVal=0,iPos=0;
    if(strSend.count()>=iChLng)return iPos;
    for(int i=0;i<=strSend.count();i++){
        if(i==strSend.count()){
            iVal=str.toInt(&ok,16);
            if(ok){
                chOut[iPos++]=iVal;
//                qDebug()<<"tosend"<<iVal;
            };
            str.clear();
            break;
        }
        if(strSend.at(i)==' '){
            iVal=str.toInt(&ok,16);
            if(ok){
                chOut[iPos++]=iVal;
//                qDebug()<<"tosend"<<iVal;
            };
            str.clear();
            continue;
        }
        str.append(strSend.at(i));
    }
    return iPos;
}

QString CharCoder::decodeToUTF8(const char *data, int iCnt){
    QString str="";
    str=QString::fromLocal8Bit(data,iCnt);
    return str;
}

// проблемы при работе с UTF,для декодирования требуется 2 байта
QString CharCoder::decodeToUTF16(const char *data, int iCnt){
    QString str="";
    for(int i=0;i<iCnt;i++){
        m_arrIntByte[m_iChPos++]=data[i];
        if(m_iChPos>=2){
            QByteArray byte;
            byte.append(m_arrIntByte[0]);
            byte.append(m_arrIntByte[1]);
            QTextCodec *codec=QTextCodec::codecForName("Windows-1251");
            str+=codec->toUnicode(byte);
            m_iChPos=0;
        }
    }
    return str;
}


QString CharCoder::decodeToHex(const char *data, int iCnt){
    QString str="";
    int uiVal=0;
    for(int i=0;i<iCnt;i++){
        uiVal=data[i];
//        qDebug()<<"received"<<uiVal;
        if(data[i]<0x00){
            uiVal=256+uiVal;
        }
        str+=QString( " %1" ).arg( uiVal, 1, 16 ).toUpper();
    }
    return str;
}


