#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include <QString>
#include <QChar>
#include <QPlainTextEdit>
static const int MAX_IN_LINE=40;

class ConsoleView : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ConsoleView(QWidget *parent = 0,QString strbeginline="out");
    ~ConsoleView();
    void      clearOld();
public slots:
    void      putData(const char *data, int iCnt);
signals:
    void      sendDataOut(const char *data,int iCnt);
protected:
    void    mousePressEvent(QMouseEvent *e);
    void    mouseDoubleClickEvent(QMouseEvent *e);
    void    keyPressEvent (QKeyEvent *e);
    void    contextMenuEvent(QContextMenuEvent *e);
private:
    int                       m_iRcvd;
    QChar                m_chSpacer;
    QString              m_strLine;
    QString              m_strBeginLine;
};

#endif // CONSOLEVIEW_HPP
