#include "charcoder.h"
#include <QTextCodec>
#include <QDebug>

CharCoder::CharCoder(){
}

int CharCoder::encode(QByteArray bytes, char *chOut,int iChLng, enmConvType convtype){
    int iLng=0;
    memset(chOut, 0, sizeof(chOut));
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QString str = codec->toUnicode(bytes);
    switch(convtype){    
    case convASCII   :
    case convUTF8    :{
        QTextCodec::setCodecForLocale(codec);
        QByteArray arr=str.toLocal8Bit();
        if(iChLng>arr.count())return -1;
        for(int i=0;i<arr.count();i++){
            chOut[i] =arr.at(i);
        }
        return (arr.count());
    }
    break;
    case convUTF16  :    {        
        ushort uVal;
        const ushort *pntUval=&(str.data()->unicode());
        if(iChLng<(str.length()*2))return errOverLng;
        for(int i=0;i<(str.length());i++){
            uVal=(*pntUval);
            if(uVal>0xFF){
                chOut[i*2]=(uVal)&0xFF;
                chOut[i*2+1]=(uVal>>8)&0xFF;
                iLng=i*2+1;
            }else{
                chOut[i*2]=0;
                chOut[i*2+1]=(uVal)&0xFF;
                iLng=i*2+1;
            }
            pntUval++;
        }
        return (++iLng);
    }
        break;
    case convHEX     :
        bool     ok;
        uchar    hex;
        QByteArray oneByte;
        for(int i=0;i<=bytes.count();i++){
            if(i==bytes.count()){
                hex = oneByte.toInt(&ok, 16);
                if(ok){
                    chOut[iLng++]=hex;
                    if(iChLng<(bytes.count()))return errOverLng;
                }else return errConv;
                break;
            }
            if(bytes.at(i)==' '){
                hex = oneByte.toInt(&ok, 16);
                if(ok){
                    chOut[iLng++]=hex;
                    if(iChLng<(bytes.count()))return errOverLng;
                }else return errConv;
                oneByte.clear();
                continue;
            }
            oneByte.append(bytes.at(i));
        }
        return iLng;
        break;
    }
    return errNoneConv;
}

QString CharCoder::decode(char *chOut, int iChLng, enmConvType convtype){
    QString strOut="";
    switch(convtype){
    case convASCII   :
    case convUTF8    :
        strOut=QString::fromAscii(chOut,iChLng);
        break;
    break;
    case convUTF16  :
        strOut=QString::fromLocal8Bit(chOut,iChLng);
        break;
    case convHEX     :
        for(int i=0;i<iChLng;i++){
            strOut.append(chOut[i]);
        }
        break;
    }    
    return strOut    ;
}


