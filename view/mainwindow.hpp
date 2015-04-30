#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>

#include "consoleview.hpp"
#include "./view/viewportadaptor.hpp"
#include "./view/comportview.hpp"
#include "../cntr/port/portinterface.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
public slots:
    void                    portSelected();
    void                    changePortState(bool bOpen);
    void                    showPorts();    
signals:    
private:    
    QLabel              *m_lblMain;
    QLabel              *m_lblStatus;
    QLabel              *m_lblPort;
    ConsoleView     *m_cnslIn;
    ConsoleView     *m_cnslOut;    

    QAction             *m_actEdit;
    QAction             *m_actShowPorts;
    QAction             *m_actConnect;
    QAction             *m_actSetting;
    QAction             *m_actQuit;
    QPushButton    *m_btnLd;

    ComPortView        *m_viewCom;
    ViewPortAdaptor  *m_adaptor;
    PortInterface         *m_port;    

    void                    prepareView();
    void                    prepareActions();
    void                    prepareElements();
    void                    prepareSignSlots();
};

#endif // MAINWINDOW_HPP
