#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <QString>
#include <QChar>
#include <QPlainTextEdit>
#include "../cmn/charcoder.h"

static const int MAX_IN_LINE  =40;
static const int CNS_WIDTH      =320;
static const int CNS_HEIGHT    =180;
static const int MAX_CHARS     =256;
static const int MAX_PREV       =10;

//class ConsoleView : public QPlainTextEdit{
class ConsoleView : public QTextEdit{
    Q_OBJECT
public:
    explicit ConsoleView(QWidget *parent = 0,QString strbeginline="out");
    ~ConsoleView();
    void      clearOld();
public slots:
    void      putData(const char *data, int iCnt);
    void      setConvType(enmConvType typeConv){m_typeConv=typeConv;}
signals:
    void      sendDataOut(const char *data,int iCnt);
protected:
    void    mousePressEvent(QMouseEvent *e);
    void    mouseDoubleClickEvent(QMouseEvent *e);
    void    keyPressEvent (QKeyEvent *e);
    void    contextMenuEvent(QContextMenuEvent *e);
private:
    int                       m_iRcvd;
    int                       m_chPos;


    bool                    m_bCmdFull;
    int                       m_iCmdPos;
    QStringList       m_lstCmdPrev;

    char                    m_chIn[MAX_CHARS];
    char                    m_chOut[MAX_CHARS];
    QByteArray       m_sendStr;
    QByteArray       m_inStr;

    enmConvType   m_typeConv;

    QChar                m_chSpacer;
    QString              m_strBeginLine;
    CharCoder       *m_coder;
};

#endif // CONSOLEVIEW_HPP
