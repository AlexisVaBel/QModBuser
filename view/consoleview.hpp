#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <QString>
#include <QStringList>
#include <QTimer>
#include <QPlainTextEdit>
#include "../cmn/charcoder.h"
#include "../rw/rwprovider.hpp"

static const int MAX_IN_LINE  =40;
static const int CNS_WIDTH      =320;
static const int CNS_HEIGHT    =180;
static const int TIME_IDLE        =50;   // 50 msecs to detect stop sending
static const int MAXBLOCKCNT=1000;



class ConsoleView : public QTextEdit{
    Q_OBJECT
public:
    explicit ConsoleView(QWidget *parent = 0, QString strStartLn="out");
    ~ConsoleView();

    void      clearOld();
    RWProvider      *getReader(){return m_reader;}
    RWProvider      *getWriter(){return m_writer;}
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
    int                       m_iIdx;
    CharCoder       *m_coder;
    QStringList         m_lstSend;
    RWProvider      *m_reader;
    RWProvider      *m_writer;

    QTimer              *m_timerIdle;        // to get idle in line
    QString              m_strStartLn;
    enmConvType   m_convType;

    void                    goPrevCmds();
};

#endif // CONSOLEVIEW_HPP
