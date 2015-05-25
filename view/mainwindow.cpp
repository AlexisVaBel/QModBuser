#include "mainwindow.hpp"
#include "../cntr/port/comport.hpp"
#include <termios.h>
#include <QToolBar>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QThread>

#include <QDebug>
#include <QStandardItemModel>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    prepareElements();
    prepareView();    
    prepareActions();
    prepareSignSlots();
}

void MainWindow::portSelected(){
    m_lblPort->setText(m_viewCom->getPortWithPrms());
}

void MainWindow::changePortState(bool bOpen){
    if(!bOpen){        
        m_lblStatus->setText(QString(" Disconnected"));
        m_lblStatus->setFont(QFont("Times", 12, QFont::Light));
        m_actConnect->setText(tr("Connect"));        
        m_adaptor->stopListenPort();
    }else{
        m_actConnect->setText(tr("Disconnect"));
        SerialParams prmIn;        
        prmIn=m_viewCom->getParams();
        if(prmIn.strPort.empty()){
            qDebug()<<"can`t open";
            m_actConnect->toggle();
            return;
        }
        if(!m_adaptor->startListenPort(prmIn)){
            qDebug()<<"can`t open";
            m_actConnect->toggle();
            return;
        }
        m_lblStatus->setText(QString(" Connected"));
        m_lblStatus->setFont(QFont("Times", 12, QFont::Bold));
    }
}

void MainWindow::showPorts(){    
    m_viewCom->show();
}

void MainWindow::showGraph(){
    m_painter->show();        
    for(int i=0;i<1000;i++){
        m_painter->appendData(QDateTime::currentMSecsSinceEpoch(),i);
        m_painter->refreshPlot();
    }
    m_painter->getVectorData();
}

void MainWindow::prepareView(){
    QHBoxLayout *ltConsole,*ltControl,*ltParams;
    QVBoxLayout *ltMain;
    ltMain      =new QVBoxLayout();
    ltConsole  =new QHBoxLayout();
    ltControl  =new QHBoxLayout();
    ltParams  =new QHBoxLayout();

    m_lblMain    = new QLabel();
    m_lblPort     = new QLabel();
    m_lblStatus  = new QLabel();

    m_btnLd         =  new QPushButton();
    m_viewCom    =  new ComPortView();
    m_painter       =new PlotPainter();

    m_viewCom->setModal(true);
    m_viewCom->setAdaptor(m_adaptor);

    m_lblPort->setText(QString("------"));
    m_lblStatus->setText(QString("Disconnected"));

    ltConsole->addWidget(m_cnslIn);
    ltConsole->addWidget(m_cnslOut);
    ltControl->addWidget(m_btnLd);
    ltControl->addStretch();
    ltControl->addWidget(m_lblPort);
    ltControl->addWidget(m_lblStatus);
    ltControl->addStretch();

    ltMain->addLayout(ltConsole);
    ltMain->addLayout(ltParams);
    ltMain->addLayout(ltControl);

    m_lblMain->setLayout(ltMain);
    setCentralWidget(m_lblMain);
    setMinimumSize(800,520);
}

void MainWindow::prepareActions(){
    m_actEdit              =new QAction(tr("Edit"),this);
    m_actShowPorts   =new QAction(tr("ShowPorts"),this);
    m_actSetting         =new QAction(tr("Setting"),this);
    m_actQuit             =new QAction(tr("Quit"),this);
    m_actShowGraph =new QAction(tr("Graph"),this);
    m_actConnect    =new QAction(tr("Connect"),this);
    m_actConnect->setCheckable(true);

    QToolBar            *toolsUp          =new QToolBar("ToolsUp",this);
    QToolBar            *toolsBottom  =new QToolBar("ToolsBottom",this);

    toolsUp->addAction(m_actEdit);
    toolsUp->addAction(m_actSetting);
    toolsUp->addAction(m_actShowGraph);
    toolsBottom->addAction(m_actShowPorts);
    toolsBottom->addAction(m_actConnect);
    toolsBottom->addSeparator();
    toolsBottom->addAction(m_actQuit);
    addToolBar(Qt::TopToolBarArea,toolsUp);
    addToolBar(Qt::BottomToolBarArea,toolsBottom);
}

void MainWindow::prepareElements(){    
    m_cnslIn         =  new ConsoleView (this,"in :");
    m_cnslOut      =  new ConsoleView (this,"out:");
    m_port            =new COMPort();    
    m_adaptor=new ViewPortAdaptor(this);
    m_adaptor->setViews(m_cnslIn,m_cnslOut);
    m_adaptor->setPorts(m_port);
}

void MainWindow::prepareSignSlots(){  
  connect(m_actConnect      ,SIGNAL(toggled(bool)),this,SLOT(changePortState(bool)));
  connect(m_actShowPorts  ,SIGNAL(triggered()),this,SLOT(showPorts()));
  connect(m_actShowGraph,SIGNAL(triggered()),this,SLOT(showGraph()));
//  connect(m_actShowGraph,SIGNAL(triggered()),m_painter,SLOT(show()));
//  connect(m_actEdit             ,SIGNAL(triggered()),this,SLOT(showPorts()));
//  connect(m_actSetting        ,SIGNAL(triggered()),this,SLOT(showPorts()));
  connect(m_actQuit            ,SIGNAL(triggered()),this,SLOT(close()));
  connect(m_viewCom          ,SIGNAL(accepted()),this,SLOT(portSelected()));
}
