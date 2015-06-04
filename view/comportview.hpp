#ifndef COMPORTVIEW_HPP
#define COMPORTVIEW_HPP

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include "./view/viewportadaptor.hpp"

class ComPortView : public QDialog
{
    Q_OBJECT
public:
    explicit ComPortView(QWidget *parent = 0);
    void      setAdaptor(ViewPortAdaptor *adaptor);
    QString          getPortWithPrms(){return (m_strPort+"//"+m_cmbBaud->currentText()+"//"+m_cmbDataBits->currentText()+
                                               "//"+m_cmbStopBits->currentText()+"//"+m_cmbFlow->currentText());}
    QString          getPortName()    {return m_strPort;}
    SerialParams getParams()        {return m_serialPrms;}
signals:

public slots:
    void     enCodeParams();
    void     deCodeParams();
    void     showPortName(QModelIndex idx);
    void     setPreferedParams();
    void     showPortParams(QModelIndex idx);
    void     okPressed();
    void     cancelPressed();
private:
    QComboBox              *m_cmbBaud;
    QComboBox              *m_cmbDataBits;
    QComboBox              *m_cmbStopBits;
    QComboBox              *m_cmbFlow;

    QPushButton             *m_btnOk;
    QPushButton             *m_btnCancel;
    QTableWidget           *m_tblPrms;
    QListWidget              *m_lstPorts;
    ViewPortAdaptor     *m_adaptor;

    QString             m_strPort;
    SerialParams    m_serialPrms;

    QMap<int,QString> m_mapBaud;

    void    loadPorts();

    void    prepareBaudMap();
    void    prepareView();
    void    prepareSignSlots();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};

#endif // COMPORTVIEW_HPP
