#ifndef CHARCODER_H
#define CHARCODER_H
#include <QString>

enum enmConvType{
    convASCII=0,convUTF8=1,convUTF16=2,convHEX=3
};

enum enmErrConv{
    errOverLng=-1,errNoneConv=-2,errConv=-3
};

class CharCoder{
public:
    CharCoder();
    ~CharCoder();
//    int encode(QString strSend, char*chOut, int iChLng, enmConvType convtype);
    int encodToUTF8(QString strSend, char*chOut, int iChLng);
    int encodToUTF16(QString strSend, char*chOut, int iChLng);
    int encodToHEX(QString strSend, char*chOut, int iChLng);
    QString decodeToUTF8(const char *data, int iCnt);
    QString decodeToUTF16(const char *data, int iCnt);
    QString decodeToHex(const char *data, int iCnt);
private:
    int           m_iChPos;
    ushort     m_arrIntByte[2];
};

#endif // CHARCODER_H
