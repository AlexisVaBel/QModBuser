#ifndef ENCODEVIEW_H
#define ENCODEVIEW_H

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include "../cmn/charcoder.h"

class EncodeView : public QDialog
{
    Q_OBJECT
public:
    explicit EncodeView(QWidget *parent = 0);
    enmConvType m_convType;

signals:
    void    okPressed(enmConvType codeType);
public slots:
    void    pressOk();
private:

    QRadioButton    *m_radUTF8;
    QRadioButton    *m_radUTF16;
    QRadioButton    *m_radHEX;
    QPushButton      *m_btnOk;
    QPushButton      *m_btnCancel;


    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};

#endif // ENCODEVIEW_H
