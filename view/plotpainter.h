#ifndef PLOTPAINTER_H
#define PLOTPAINTER_H

#include <QLabel>
#include <QDateTime>
#include <QVector>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_marker.h>
#include <qwt_scale_draw.h>
#include <qwt_symbol.h>
#include <QPainter>
#include <QRubberBand>
#include "../cmn/timescaledraw.h"

static const   int MIN_PNL_WIDTH=920;
static const   int MIN_PNL_HEIGTH=740;


class PlotPainter : public QLabel
{
    Q_OBJECT
public:
    explicit PlotPainter(QWidget *parent=0,double dUpY=60,double dLowY=-60);
    void            adjustXY();
    void            adjustCurve();
    void            setYAxis(double dLow,double dUp);
    void            scrollX(int dx);
    void            changeYAxis(double dLow,double dUp);
    void            changeXAxis(double dLow,double dUp);
    void            appendData(double dTime,double dValue);
    void            setPlotName(QString qstrName);
    void            setPrinterData(QPrinter &printer);
    void            setDataHolders(QVector<double>* vctTime,QVector<double> *vctValue);
    void            getVectorData();

    double          getYLow();
    double          getYUp();
signals:

public slots:
    void            clearPlot();
    void            refreshPlot();
    void            enableZoom();
    void            disableZoom();
    void            enableMarker();
    void            disableMarker();
    void            enableObserver();
    void            disableObserver();
    void            setCurveData();
    void            setMarker(QPointF pntSet);
    void            setMarker(int iDataIndex);
    void            onSelect(const QPointF &);
    void            resizePlot(int w,int h);
private:
    QLabel                  *m_lblMain;
    QwtPlot                 *m_pltMain;
    QwtPlotCurve       *m_curveMain;
    QwtPlotMarker    *m_markerMain;
    QwtPlotPicker      *m_pickerMain;
    QwtPlotGrid         *m_gridMain;
    QRubberBand       *m_rbrBRect;
    QVector<double> *m_vctdTime;
    QVector<double> *m_vctdValue;

    bool            m_bZoom;
    bool            m_bMarker;

    double          m_dBaseUpY;
    double          m_dBaseLowY;
    double          m_dScrollUpX;
    double          m_dScrollLowX;

    double          m_dLowX;
    double          m_dLowY;
    double          m_dUpX;
    double          m_dUpY;
    QPoint          m_qpntRbrPos;

    void            prepareView();    
    void            prepareAxis();
    void            prepareGraphics();

    void            setYAxisToBase();
    void            setXAxisToBase();
protected:
    void            mousePressEvent(QMouseEvent *event);
    void            mouseReleaseEvent(QMouseEvent *event);
    void            mouseMoveEvent(QMouseEvent *event);
};

#endif // PLOTPAINTER_H
#include <QLabel>
#include <qwt_plot.h>
