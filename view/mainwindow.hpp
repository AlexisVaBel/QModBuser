#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>

#include "consoleview.hpp"

#include "./view/encodeview.hpp"
#include "./cntr/rwadaptor.hpp"
#include "./view/comportview.hpp"
#include "../port/portinterface.hpp"
#include "../port/portfactory.hpp"



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void                    portSelected();
    void                    changePortState(bool bOpen);
    void                    loadDevice();
    void                    showPorts();
    void                    showEncode();
    void                    clearOut();
    void                    clearIn();
signals:    
private:    
    QLabel              *m_lblMain;
    QLabel              *m_lblStatus;
    QLabel              *m_lblPort;    
    ConsoleView     *m_cnslIn;
    ConsoleView     *m_cnslOut;    

    QAction             *m_actShowPorts;
    QAction             *m_actConnect;
    QAction             *m_actQuit;

    QAction             *m_actEncode;
    QAction             *m_actClrIn;
    QAction             *m_actClrOut;
    QAction             *m_actDevice;
    QPushButton    *m_btnLd;

    ComPortView        *m_viewCom;
    EncodeView           *m_viewEnc;

    PortInterface         *m_port;        
    PortFactory           *m_factPort;

    RWAdaptor  *m_adaptor;



    void                    prepareView();
    void                    prepareAdaptor();
    void                    prepareFactory();
    void                    prepareActions();
    void                    prepareElements();
    void                    prepareSignSlots();
};

#endif // MAINWINDOW_HPP
