#include "consoleview.hpp"
#include <QDebug>

ConsoleView::ConsoleView(QWidget *parent, QString strbeginline) :
    QPlainTextEdit(parent){
    m_iRcvd                 =0;
    m_strBeginLine    =strbeginline;
    m_strLine               ="";
    m_chSpacer            =QChar(' ');    
    QPalette                p=palette();
    setMinimumSize(QSize(320,180));
    document()->setMaximumBlockCount(1000);
    p.setColor(QPalette::Base,Qt::black);
    p.setColor(QPalette::Text,Qt::green);
    setPalette(p);    
    insertPlainText(m_strBeginLine);
}

ConsoleView::~ConsoleView(){
}

void ConsoleView::putData(const char *data, int iCnt){
    int iVal;
    if(m_iRcvd>MAX_IN_LINE){
        insertPlainText(tr("\r\n"));
        m_iRcvd=0;
    }
    if(m_iRcvd==0){insertPlainText(tr("in:   "));};
//    insertPlainText(QString(data));
    for (int i=0;i<iCnt;i++){
        m_iRcvd++;
        iVal=QChar(data[i]).toLatin1();
        insertPlainText(QString::number(iVal));
        if(!m_chSpacer.isLetter())insertPlainText(m_chSpacer);
    };
}

void ConsoleView::clearOld(){
    this->clear();
}

void ConsoleView::mousePressEvent(QMouseEvent *e){
    Q_UNUSED(e);
    setFocus();
}

void ConsoleView::mouseDoubleClickEvent(QMouseEvent *e){
    Q_UNUSED(e);
}

void ConsoleView::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case    Qt::Key_Backspace:
    case    Qt::Key_Left:
    case    Qt::Key_Right:
    case    Qt::Key_Down:
        break;
    case    Qt::Key_Return:
    case    Qt::Key_Enter:
        if(!m_strLine.isEmpty()){
            emit     sendDataOut(m_strLine.toStdString().c_str(),m_strLine.toStdString().size());
            m_iRcvd=0;
        }
        m_strLine.clear();
        QPlainTextEdit::keyPressEvent(e);
        insertPlainText(m_strBeginLine);
        break;
    default:
        QPlainTextEdit::keyPressEvent(e);
        m_strLine.append(e->text());
    }
}

void ConsoleView::contextMenuEvent(QContextMenuEvent *e){
    Q_UNUSED(e);
}
