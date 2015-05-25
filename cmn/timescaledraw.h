#ifndef TIMESCALEDRAW_H
#define TIMESCALEDRAW_H
#include <qwt_scale_draw.h>
#include <QDateTime>
#include <math.h>
class TimeScaleDraw:public QwtScaleDraw{
public:
    TimeScaleDraw(QString fmt):format(fmt){}
    virtual         QwtText label(double v) const{
                    return (QDateTime::fromMSecsSinceEpoch(floor(v))).toString(format);
    }
private:
    const           QString format;
};
#endif // TIMESCALEDRAW_H
