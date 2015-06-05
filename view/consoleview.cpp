#include "consoleview.hpp"
#include <QTextCodec>
#include <QTextBlock>

ConsoleView::ConsoleView(QWidget *parent, QString strStartLn) :
    QTextEdit(parent){    
    m_strStartLn       =    strStartLn;
    m_convType         =    convHEX;
    m_timerIdle         =    new QTimer(this);
    m_timerIdle->setInterval(TIME_IDLE);
    m_timerIdle->setSingleShot(true);

    m_coder               =new CharCoder();
    QPalette              p=palette();
    setMinimumSize(QSize(CNS_WIDTH,CNS_HEIGHT));
    document()->setMaximumBlockCount(1000);
    p.setColor(QPalette::Base,Qt::black);
    p.setColor(QPalette::Text,Qt::green);
    setPalette(p);    
    insertPlainText(m_strStartLn);
    connect(m_timerIdle,SIGNAL(timeout()),SLOT(createNextLine()));
}

ConsoleView::~ConsoleView(){
}

void ConsoleView::getData(const char *data, int iCnt){
    QString str="";
    if(m_timerIdle->isActive()){m_timerIdle->stop();}
    if((m_convType==convASCII)||(m_convType==convUTF8)){
        str=m_coder->decodeToUTF8(data,iCnt);
        if(str.contains(0x0A))str.append(m_strStartLn);
    }else
        if(m_convType==convUTF16){
            str=m_coder->decodeToUTF16(data,iCnt);
        }
        else
        if(m_convType==convHEX){
            str=m_coder->decodeToHex(data,iCnt);
            m_timerIdle->start();
        }
    if(!str.isEmpty()) {
        insertPlainText(str);
        this->moveCursor(QTextCursor::End);
    }
}

void ConsoleView::sendConvData(){
    QString strSend=this->textCursor().block().text();
    strSend=strSend.remove(m_strStartLn);
    if(strSend.isEmpty())return;

    int iCnt;
    char *pntCh;
    char chOut[256];
    memset(&chOut,0,sizeof(chOut));
    pntCh=&chOut[0];
    if((m_convType==convASCII)||(m_convType==convUTF8)){        
        iCnt=m_coder->encodToUTF8(strSend,pntCh,256);
    }else
    if(m_convType==convUTF16){
        iCnt=m_coder->encodToUTF16(strSend,pntCh,256);
    }
    else
    if(m_convType==convHEX){
        iCnt=m_coder->encodToHEX(strSend,pntCh,256);
    }
    emit     sendDataOut(pntCh,iCnt);
}

void ConsoleView::createNextLine(){
    insertPlainText("\r\n"+m_strStartLn);
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
    case    Qt::Key_Backspace:{
        if(this->textCursor().block().text().compare(m_strStartLn,Qt::CaseInsensitive)==0)break;
            this->textCursor().deletePreviousChar();        
    }
    break;
    case    Qt::Key_Left:                
    case    Qt::Key_Right:
    case    Qt::Key_Down:
        break;
    case    Qt::Key_Up:
        break;
    case    Qt::Key_Return:
    case    Qt::Key_Enter:        
            sendConvData();            
        QTextEdit::keyPressEvent(e);
        insertPlainText(m_strStartLn);
        break;
    default:
        QTextEdit::keyPressEvent(e);        
    }
}

void ConsoleView::contextMenuEvent(QContextMenuEvent *e){
    Q_UNUSED(e);
}
