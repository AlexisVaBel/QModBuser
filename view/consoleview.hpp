#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <QString>
#include <QTimer>
#include <QPlainTextEdit>
#include "../cmn/charcoder.h"
#include <QDebug>

static const int MAX_IN_LINE  =40;
static const int CNS_WIDTH      =320;
static const int CNS_HEIGHT    =180;
static const int TIME_IDLE  =50;   // 200 msecs to detect stop sending



class ConsoleView : public QTextEdit{
    Q_OBJECT
public:
    explicit ConsoleView(QWidget *parent = 0, QString strStartLn="out");
    ~ConsoleView();
    void      clearOld();
public slots:
    void      getData(const char *data, int iCnt);
    void      sendConvData();
    void      createNextLine();

    void                       setConvType(enmConvType convType){m_convType=convType;}
    enmConvType      getConvType(){return m_convType;}
signals:
    void      sendDataOut(const char *data,int iCnt);
protected:
    void    mousePressEvent(QMouseEvent *e);
    void    mouseDoubleClickEvent(QMouseEvent *e);
    void    keyPressEvent (QKeyEvent *e);
    void    contextMenuEvent(QContextMenuEvent *e);
private:    
//    QByteArray       m_oneByte;
    int                       m_iChPos;
    ushort                m_arrIntByte[2];

    QTimer              *m_timerIdle;        // to get idle in line
    QString              m_strStartLn;
    volatile enmConvType   m_convType;
};

#endif // CONSOLEVIEW_HPP
