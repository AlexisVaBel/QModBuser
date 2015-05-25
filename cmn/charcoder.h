#ifndef CHARCODER_H
#define CHARCODER_H
#include <QString>

enum enmConvType{
    convASCII=0,convUTF8,convUTF16,convHEX
};

enum enmErrConv{
    errOverLng=-1,errNoneConv=-2,errConv=-3
};


class CharCoder{
public:
    CharCoder();
    int encode(QByteArray bytes, char*chOut, int iChLng, enmConvType convtype);
    QString decode(char*chOut, int iChLng, enmConvType convtype);
};

#endif // CHARCODER_H
