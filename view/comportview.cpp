#include "comportview.hpp"
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <termios.h>

#include <QDebug>

ComPortView::ComPortView(QWidget *parent) :
    QDialog(parent){
    prepareBaudMap();
    prepareView();
    prepareSignSlots();
}

void ComPortView::setAdaptor(ViewPortAdaptor *adaptor){
    m_adaptor=adaptor;
}

void ComPortView::enCodeParams(){
    QTableWidgetItem *itemVal;
    itemVal     =new QTableWidgetItem(m_strPort);
    m_tblPrms->setItem(0,1,itemVal);
    QString strMap=m_mapBaud.value(m_serialPrms.iBaudRate);
    for(int i=0;i<=m_cmbBaud->count();i++){
        if((QString::compare(strMap,m_cmbBaud->itemText(i)))==0){
            m_cmbBaud->setCurrentIndex(i);
            break;
        }
    }
    switch(m_serialPrms.iDataBits){
    case    CS5:m_cmbDataBits->setCurrentIndex(0);break;
    case    CS6:m_cmbDataBits->setCurrentIndex(1);break;
    case    CS7:m_cmbDataBits->setCurrentIndex(2);break;
    case    CS8:m_cmbDataBits->setCurrentIndex(3);break;
    }
    switch(m_serialPrms.iStopBits){
    case    CSTOPB  :m_cmbStopBits->setCurrentIndex(1);break;
    default                 :m_cmbStopBits->setCurrentIndex(0);break;
    }
    switch(m_serialPrms.iFlowCnt){
    case    (PARENB):m_cmbFlow->setCurrentIndex(1);break;
    case    (PARENB|PARODD):m_cmbFlow->setCurrentIndex(2);break;
    default       :m_cmbFlow->setCurrentIndex(0);break;
    }
}

void ComPortView::deCodeParams(){
    QString strMap="",strCmb="";
    strCmb=m_cmbBaud->currentText();
    foreach (int iVal, m_mapBaud.keys()) {
        strMap=m_mapBaud.value(iVal);
        qDebug()<<iVal<<strMap<<strCmb;
        if(QString::compare(strMap,strCmb,Qt::CaseInsensitive)==0){
            m_serialPrms.iBaudRate=iVal;
            qDebug()<<iVal<<m_mapBaud.value(iVal);
            break;
        }
    }
    switch(m_cmbDataBits->currentIndex()){
    case 0: m_serialPrms.iDataBits=CS5; break;
    case 1: m_serialPrms.iDataBits=CS6; break;
    case 2: m_serialPrms.iDataBits=CS7; break;
    case 3: m_serialPrms.iDataBits=CS8; break;
    }
    switch(m_cmbStopBits->currentIndex()){
    case 0: m_serialPrms.iStopBits=0             ; break;
    case 1: m_serialPrms.iStopBits=CSTOPB; break;
    }
    switch(m_cmbFlow->currentIndex()){
    case 0: m_serialPrms.iFlowCnt=0; break;
    case 1: m_serialPrms.iFlowCnt=PARENB                    ; break;
    case 2: m_serialPrms.iFlowCnt=(PARENB|PARODD); break;
    }
    m_serialPrms.strPort=m_strPort.toStdString();
}

void ComPortView::showPortName(QModelIndex idx){
    if (!idx.isValid())return;
    m_strPort=idx.data().toString();
    QTableWidgetItem *itemVal;
    itemVal     =new QTableWidgetItem(m_strPort);
    m_tblPrms->setItem(0,1,itemVal);
}

void ComPortView::showPortParams(QModelIndex idx){
    if (!idx.isValid())return;
    m_strPort=idx.data().toString();
    m_serialPrms=m_adaptor->getPortPrms(m_strPort);
    enCodeParams();
}

void ComPortView::okPressed(){
    deCodeParams();
    emit accept();
}

void ComPortView::cancelPressed(){
    m_strPort.clear();
    emit reject();
}

void ComPortView::loadPorts(){
    m_strPort.clear();
    QStringList lst=m_adaptor->getPorts();
    if(lst.isEmpty())return;
    m_lstPorts->clear();
    m_lstPorts->addItems(lst);
}

void ComPortView::prepareBaudMap(){
// octal constants
    QString str="";
    for(int i=0000;i<00020;i++){
        switch(i){
        case 0000:str="-----";break;
        case 0001:str="B50";break;
        case 0002:str="B75";break;
        case 0003:str="B110";break;
        case 0004:str="B134";break;
        case 0005:str="B150";break;
        case 0006:str="B200";break;
        case 0007:str="B300";break;
        case 0010:str="B600";break;
        case 0011:str="B1200";break;
        case 0012:str="B1800";break;
        case 0013:str="B2400";break;
        case 0014:str="B4800";break;
        case 0015:str="B9600";break;
        case 0016:str="B19200";break;
        case 0017:str="B38400";break;
        }
        m_mapBaud.insert(i,str);
    }
    for(int i=010001;i<010020;i++){
        switch(i){
        case 010001:str="B57600";break;
        case 010002:str="B115200";break;
        case 010003:str="B230400";break;
        case 010004:str="B460800";break;
        case 010005:str="B500000";break;
        case 010006:str="B576000";break;
        case 010007:str="B921600";break;
        case 010010:str="B1000000";break;
        case 010011:str="B1152000";break;
        case 010012:str="B1500000";break;
        case 010013:str="B2000000";break;
        case 010014:str="B2500000";break;
        case 010015:str="B3000000";break;
        case 010016:str="B3500000";break;
        case 010017:str="B4000000";break;
        }
        m_mapBaud.insert(i,str);
    }
}

void ComPortView::prepareView(){
    QHBoxLayout *ltControl,*ltView;
    QVBoxLayout *ltMain;
    ltMain      =new QVBoxLayout();
    ltView       =new QHBoxLayout();
    ltControl  =new QHBoxLayout();

    m_tblPrms   =new QTableWidget();
    m_lstPorts    =new QListWidget();
    m_btnOk      =new QPushButton(tr("Ok"));
    m_btnCancel=new QPushButton(tr("NOk"));
    m_cmbBaud         =new QComboBox();
    m_cmbDataBits   =new QComboBox();
    m_cmbStopBits    =new QComboBox();
    m_cmbFlow          =new QComboBox();

    m_cmbDataBits->addItem(QString("CS5"));
    m_cmbDataBits->addItem(QString("CS6"));
    m_cmbDataBits->addItem(QString("CS7"));
    m_cmbDataBits->addItem(QString("CS8"));
    m_cmbStopBits->addItem(QString("STOP_1"));
    m_cmbStopBits->addItem(QString("STOP_2"));
    m_cmbFlow->addItem(QString("NONE"));
    m_cmbFlow->addItem(QString("PARENB"));
    m_cmbFlow->addItem(QString("PARODD"));
    foreach(int iVal,(m_mapBaud.keys())){
        m_cmbBaud->addItem(m_mapBaud.value(iVal));
    }
// prepare table
    QFont fnt;
    QString str;
    QTableWidgetItem *item,*item2;
    m_tblPrms->setRowCount(5);
    m_tblPrms->setColumnCount(2);
    str=QString("Parameter").toLocal8Bit();
    item=new QTableWidgetItem(str);
    str=QString("Value").toLocal8Bit();
    item2=new QTableWidgetItem(str);
    fnt=item->font();
    fnt.setBold(true);
    item->setFont(fnt);
    fnt=item2->font();
    fnt.setBold(true);
    item2->setFont(fnt);
    m_tblPrms->setHorizontalHeaderItem(0,item);
    m_tblPrms->setHorizontalHeaderItem(1,item2);
    m_tblPrms->setColumnWidth(0,m_tblPrms->width()/4);
    m_tblPrms->setColumnWidth(1,m_tblPrms->width()/4);
    m_tblPrms->verticalHeader()->setVisible(false);
    for(int i=0;i<5;i++){
        switch(i){
        case 0:  str=QString("Port");
        break;
        case 1:  str=QString("BaudRate");
        break;
        case 2:  str=QString("DataBits");
        break;
        case 3:  str=QString("StopBits");
        break;
        case 4:  str=QString("Flow");
        break;
        }
        item2=new QTableWidgetItem(str);
        m_tblPrms->setItem(i,0,item2);
    }
    m_tblPrms->resizeRowsToContents();
    m_tblPrms->setColumnWidth(0,(m_tblPrms->width()/4));
    m_tblPrms->setColumnWidth(1,(m_tblPrms->width()/4));
    m_tblPrms->setCellWidget(1,1,m_cmbBaud);
    m_tblPrms->setCellWidget(2,1,m_cmbDataBits);
    m_tblPrms->setCellWidget(3,1,m_cmbStopBits);
    m_tblPrms->setCellWidget(4,1,m_cmbFlow);
// prepare table
    ltView->addWidget(m_tblPrms);
    ltView->addWidget(m_lstPorts);
    ltControl->addStretch();
    ltControl->addWidget(m_btnOk);
    ltControl->addWidget(m_btnCancel);

    ltMain->addLayout(ltView);
    ltMain->addLayout(ltControl);
    setLayout(ltMain);
    setFixedSize(680,300);
}

void ComPortView::prepareSignSlots(){
    connect(m_btnOk        ,SIGNAL(clicked())                                       ,this,SLOT(okPressed()));
    connect(m_btnCancel ,SIGNAL(clicked())                                       ,this,SLOT(cancelPressed()));
    connect(m_lstPorts      ,SIGNAL(doubleClicked(QModelIndex))  ,this,SLOT(showPortParams(QModelIndex)));
    connect(m_lstPorts      ,SIGNAL(clicked(QModelIndex))               ,this,SLOT(showPortName(QModelIndex)));
}

void ComPortView::showEvent(QShowEvent *){
    if(m_adaptor==0)return;
    loadPorts();
}
