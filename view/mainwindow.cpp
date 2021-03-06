#include "mainwindow.hpp"
#include <assert.h>

#include <QToolBar>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStringListModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
    prepareFactory();
    prepareElements();
    prepareView();    
    prepareActions();
    prepareAdaptor();
    prepareSignSlots();
}

MainWindow::~MainWindow(){
    delete m_actShowPorts;
    delete m_actConnect;
    delete m_actQuit;
    delete m_actEncode;
    delete m_actClrIn;
    delete m_actClrOut;
    delete m_actDevice;
    delete m_viewCom;
    delete m_viewEnc;
    delete m_adaptor;
    delete m_port;
}

void MainWindow::portSelected(){    
    m_lblPort->setText(m_viewCom->getPortWithPrms());
    m_actConnect->trigger();
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
            m_actConnect->toggle();
            return;
        }        
        if(!m_adaptor->startListenPort(prmIn)){            
            m_actConnect->toggle();
            return;
        }        
        m_lblStatus->setText(QString(" Connected"));
        m_lblStatus->setFont(QFont("Times", 12, QFont::Bold));
    }
}

void MainWindow::loadDevice(){

}

void MainWindow::showPorts(){    
    m_viewCom->show();
}

void MainWindow::showEncode(){
    m_viewEnc->m_convType=m_cnslIn->getConvType();
    m_viewEnc->show();
}

void MainWindow::clearIn(){
    m_cnslIn->clear();
}

void MainWindow::clearOut(){
    m_cnslOut->clear();
}


void MainWindow::prepareAdaptor(){
    assert(m_port!=NULL);
    assert(m_cnslIn!=NULL);
    assert(m_cnslOut!=NULL);
    m_adaptor=new RWAdaptor(this);
    m_adaptor->setReader(m_cnslIn->getReader());
    m_adaptor->setWriter(m_cnslOut->getWriter());
    m_adaptor->setPort(m_port);
    m_viewCom->setAdaptor(m_adaptor);
}

void MainWindow::prepareFactory(){
    m_factPort=new PortFactory();
}


void MainWindow::prepareElements(){
    assert(m_factPort!=NULL);
    m_port           = (m_factPort->createPort(QString("portlinux")));    
}

void MainWindow::prepareView(){
    QHBoxLayout *ltConsole,*ltControl,*ltParams;
    QVBoxLayout *ltMain;
    ltMain      =new QVBoxLayout();
    ltConsole  =new QHBoxLayout();
    ltControl  =new QHBoxLayout();
    ltParams  =new QHBoxLayout();

    m_cnslIn        =  new ConsoleView (this,"-->");
    m_cnslOut     =  new ConsoleView (this,"<--");
    m_lblMain    = new QLabel();
    m_lblPort     = new QLabel();
    m_lblStatus  = new QLabel();

    m_btnLd         =  new QPushButton();   // dummy button not needed at all ))) for design only
    m_viewCom    =  new ComPortView();
    m_viewEnc     =  new EncodeView();

    m_viewCom->setModal(true);

    m_viewEnc->setModal(true);

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
    m_actEncode        =new QAction(tr("Encode"),this);
    m_actClrIn           =new QAction(tr("Clear In"),this);
    m_actClrOut        =new QAction(tr("Clear Out"),this);
    m_actDevice         =new QAction(tr("Device"),this);

    m_actShowPorts   =new QAction(tr("ShowPorts"),this);
    m_actQuit             =new QAction(tr("Quit"),this);

    m_actConnect    =new QAction(tr("Connect"),this);
    m_actConnect->setCheckable(true);

    QToolBar            *toolsUp          =new QToolBar("ToolsUp",this);
    QToolBar            *toolsBottom  =new QToolBar("ToolsBottom",this);

    toolsUp->addAction(m_actEncode);
    toolsUp->addAction(m_actClrIn);
    toolsUp->addAction(m_actClrOut);
    toolsUp->addAction(m_actDevice);

    toolsBottom->addAction(m_actShowPorts);
    toolsBottom->addAction(m_actConnect);
    toolsBottom->addSeparator();
    toolsBottom->addAction(m_actQuit);
    addToolBar(Qt::TopToolBarArea,toolsUp);
    addToolBar(Qt::BottomToolBarArea,toolsBottom);
}

void MainWindow::prepareSignSlots(){  
  connect(m_actConnect      ,SIGNAL(toggled(bool)),this,SLOT(changePortState(bool)));
  connect(m_actShowPorts  ,SIGNAL(triggered()),this,SLOT(showPorts()));  
  connect(m_actQuit            ,SIGNAL(triggered()),this,SLOT(close()));
  connect(m_viewCom          ,SIGNAL(accepted()),this,SLOT(portSelected()));

  connect(m_actEncode       ,SIGNAL(triggered()),this,SLOT(showEncode()));
  connect(m_actClrIn          ,SIGNAL(triggered()),this,SLOT(clearIn()));
  connect(m_actClrOut       ,SIGNAL(triggered()),this,SLOT(clearOut()));
  connect(m_actDevice        , SIGNAL(triggered()),this,SLOT(loadDevice()));

  connect(m_viewEnc,SIGNAL(okPressed(enmConvType)),m_cnslIn,SLOT(setConvType(enmConvType)));
  connect(m_viewEnc,SIGNAL(okPressed(enmConvType)),m_cnslOut,SLOT(setConvType(enmConvType)));
}
