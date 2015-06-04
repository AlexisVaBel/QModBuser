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
    m_iChPos             =  0;

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
        str=QString::fromLocal8Bit(data,iCnt);
        if(str.contains(0x0A))str.append(m_strStartLn);
    }else
        if(m_convType==convUTF16){
            for(int i=0;i<iCnt;i++){
                m_arrIntByte[m_iChPos++]=data[i];
                if(m_iChPos>=2){                    
                    QByteArray byte;
                    byte.append(m_arrIntByte[0]);
                    byte.append(m_arrIntByte[1]);
                    QTextCodec *codec=QTextCodec::codecForName("Windows-1251");
                    str+=codec->toUnicode(byte);
                    m_iChPos=0;
                }
            }
        }
        else
        if(m_convType==convHEX){
            int uiVal=0;
            for(int i=0;i<iCnt;i++){
                uiVal=data[i];
                if(data[i]<0x00){
                    uiVal=256+uiVal;
                }
                str+=QString( " %1" ).arg( uiVal, 1, 16 ).toUpper();
            }
            m_timerIdle->start();
        }

    if(!str.isEmpty()) {
        insertPlainText(str);
        this->moveCursor(QTextCursor::End);
    }
}

void ConsoleView::createNextLine(){
    insertPlainText("\r\n"+m_strStartLn);
}

void ConsoleView::sendConvData(){
    QString strSend=this->textCursor().block().text();
    strSend=strSend.remove(m_strStartLn);
    if(strSend.isEmpty())return;
    if((m_convType==convASCII)||(m_convType==convUTF8)){
        emit     sendDataOut(strSend.toStdString().c_str(),strSend.toStdString().length());
    }else
    if(m_convType==convUTF16){        
        uint uiVal=0;
        char ch[strSend.length()*2];
        for(int i=0;i<strSend.length();i++){
            uiVal=strSend.at(i).unicode();
            ch[i*2]     =uiVal>>8;
            ch[i*2+1] =uiVal&0xFF;
        }
        emit     sendDataOut(ch,strSend.length()*2);
    }
    else{        
        bool ok=false;
        QString str="";
        int iVal=0,iPos=0;
        char ch[strSend.count()];
        for(int i=0;i<=strSend.count();i++){
            if(i==strSend.count()){
                iVal=str.toInt(&ok,16);
                if(ok){
                    ch[iPos++]=iVal;
                };
                str.clear();
                break;
            }
            if(strSend.at(i)==' '){
                iVal=str.toInt(&ok,16);
                if(ok){
                    ch[iPos++]=iVal;
                };
                str.clear();
                continue;
            }
            str.append(strSend.at(i));
        }        
        emit     sendDataOut(ch,iPos);
    }
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
