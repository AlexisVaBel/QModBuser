#include "consoleview.hpp"
#include <QDebug>

ConsoleView::ConsoleView(QWidget *parent, QString strbeginline) :
    QTextEdit(parent){
    m_coder                   =new CharCoder();
    m_iRcvd                   =0;
    m_iCmdPos             =0;
    m_chPos                   =0;
    m_bCmdFull           =false;
    m_strBeginLine      =strbeginline;
    m_typeConv            =convUTF16;
//    m_typeConv            =convASCII;
    m_chSpacer            =QChar(' ');    
    QPalette                p=palette();
    setMinimumSize(QSize(CNS_WIDTH,CNS_HEIGHT));
    document()->setMaximumBlockCount(1000);
    p.setColor(QPalette::Base,Qt::black);
    p.setColor(QPalette::Text,Qt::green);
    setPalette(p);    
    insertPlainText(m_strBeginLine);
}

ConsoleView::~ConsoleView(){
}

void ConsoleView::putData(const char *data, int iCnt){    
    int iVal=0;
    if(m_iRcvd>MAX_IN_LINE){
        insertPlainText(tr("\r\n"));
        m_iRcvd=0;
    }
    if(m_iRcvd==0){insertPlainText(tr("in:   "));};
    for (int i=0;i<iCnt;i++){
        iVal=data[i];
        qDebug()<<iVal;
        m_chIn[m_iRcvd]=data[i];
        if(m_typeConv==convUTF16){
            if(m_chPos%2==0){
            // take it
                insertPlainText(m_coder->decode(&m_chIn[0],m_iRcvd,m_typeConv));
                if(!m_chSpacer.isLetter())insertPlainText(m_chSpacer);
                m_iRcvd=0;
                continue;
            }
        }else{
            // take it
            insertPlainText(m_coder->decode(&m_chIn[0],m_iRcvd,m_typeConv));
            if(!m_chSpacer.isLetter())insertPlainText(m_chSpacer);
            m_iRcvd=0;
            continue;
        }
        m_iRcvd++;
        m_chPos++;
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
    case    Qt::Key_Backspace:{
        if(m_sendStr.length()>0){
            m_sendStr.chop(1);
            this->textCursor().deletePreviousChar();
        }
    }
    break;
    case    Qt::Key_Left:                
    case    Qt::Key_Right:
    case    Qt::Key_Down:
        break;
    case    Qt::Key_Up:
        this->textCursor().clearSelection();
        break;
    case    Qt::Key_Return:
    case    Qt::Key_Enter:
        if(!m_sendStr.isEmpty()){
            int iCntSnd=0;
            iCntSnd=m_coder->encode(m_sendStr,m_chOut,MAX_CHARS,m_typeConv);
            if(iCntSnd>0){
                emit     sendDataOut(m_chOut,iCntSnd);
            }else qDebug()<<"nothing to send"<<iCntSnd;
            m_iRcvd=0;
            if(m_iCmdPos>MAX_PREV){
                m_iCmdPos=0;
                m_bCmdFull=true;
            }else if(!m_bCmdFull){
                m_lstCmdPrev.append(m_sendStr);
                m_iCmdPos++;
            };
            if(m_bCmdFull){
                m_lstCmdPrev.replace(m_iCmdPos++,m_sendStr);
            }
            m_sendStr.clear();
        }
        QTextEdit::keyPressEvent(e);
        insertPlainText(m_strBeginLine);
        break;
    default:
        QTextEdit::keyPressEvent(e);
        m_sendStr.append(e->text().toLocal8Bit());

    }
}

void ConsoleView::contextMenuEvent(QContextMenuEvent *e){
    Q_UNUSED(e);
}
