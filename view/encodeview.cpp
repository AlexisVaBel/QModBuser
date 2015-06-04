#include "encodeview.h"

#include <QGridLayout>

EncodeView::EncodeView(QWidget *parent) :
    QDialog(parent){
    m_radUTF8       =new QRadioButton(("utf_8"));
    m_radUTF16     =new QRadioButton(tr("utf16"));
    m_radHEX        =new QRadioButton(tr("hex"));
    m_btnOk           =new QPushButton("Ok");
    m_btnCancel     =new QPushButton("Cancel");
    QGridLayout     *lt=new QGridLayout();
    m_convType        =convASCII;
    lt->addWidget(m_radUTF8,0,0);
    lt->addWidget(m_radUTF16,1,0);
    lt->addWidget(m_radHEX,2,0);
    lt->addWidget(m_btnOk,3,1);
    lt->addWidget(m_btnCancel,3,2);
    setLayout(lt);
    connect(m_btnOk,SIGNAL(pressed()),SLOT(pressOk()));
    connect(m_btnCancel,SIGNAL(pressed()),SLOT(reject()));
}

void EncodeView::pressOk(){
    enmConvType codeType=convASCII;
    if(m_radUTF16->isChecked()) codeType=convUTF16;
    else
    if(m_radHEX->isChecked())codeType=convHEX;
    emit okPressed(codeType);
    accept();
}

void EncodeView::showEvent(QShowEvent *){
    if((m_convType==convASCII)||(m_convType==convUTF8))m_radUTF8->setChecked(true);
    else
    if(m_convType==convUTF16)m_radUTF16->setChecked(true);
    else
    m_radHEX->setChecked(true);
}
