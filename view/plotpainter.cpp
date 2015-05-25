#include "plotpainter.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <qwt_picker_machine.h>
#include <qwt_plot_renderer.h>
#include <QDebug>


PlotPainter::PlotPainter(QWidget *parent, double dUpY, double dLowY):QLabel(parent){
    m_bZoom     =false;
    m_bMarker   =false;
    m_vctdTime  =new QVector<double>();
    m_vctdValue =new QVector<double>();
    m_dBaseUpY     =dUpY;
    m_dBaseLowY   =dLowY;
    m_qpntRbrPos   =QPoint(0,0);
    m_pltMain          =new QwtPlot(parent);
    m_pltMain->setMinimumSize(MIN_PNL_WIDTH,MIN_PNL_HEIGTH);
    m_rbrBRect  = new QRubberBand(QRubberBand::Rectangle, this);
    prepareView();    
    connect( m_pickerMain, SIGNAL(selected(const QPointF&)),this,
             SLOT(onSelect(const QPointF&)));
}
//*********************************************     prepare     ********************************************//
void PlotPainter::prepareView(){
    prepareGraphics();
    prepareAxis();
    QVBoxLayout *ltMain=new QVBoxLayout();
    ltMain->addWidget(m_pltMain);
    m_pltMain->installEventFilter(this);
    setLayout(ltMain);
}

void PlotPainter::prepareGraphics(){
    m_pltMain->setAutoReplot(false);
    m_pltMain->setCanvasBackground(Qt::white);    
    m_gridMain          =new QwtPlotGrid();
    m_curveMain         =new QwtPlotCurve();
    m_markerMain        =new QwtPlotMarker();
    m_pickerMain        =new QwtPlotPicker(m_pltMain->canvas());
    QwtSymbol *symbol   =new QwtSymbol(QwtSymbol::Ellipse,
                             QBrush(Qt::yellow),QPen(Qt::blue,2),QSize(3,3));
    m_markerMain->setSymbol(new QwtSymbol(QwtSymbol::Diamond,Qt::red,
                                          Qt::NoPen,QSize(5,5)));
    m_markerMain->setLabelAlignment(Qt::AlignHCenter|Qt::AlignTop);
    m_curveMain->setSymbol(symbol);
    m_gridMain->attach(m_pltMain);
}

void PlotPainter::prepareAxis(){
    m_pltMain->setAxisScaleDraw(QwtPlot::xBottom,new TimeScaleDraw("mm:ss:zzz"));
    m_pltMain->setAxisTitle(QwtPlot::xBottom,QString::fromLocal8Bit("t, ì:ñ:ìñ"));
    m_pltMain->setAxisTitle(QwtPlot::yLeft,QString::fromLocal8Bit("P, êã"));
    m_pltMain->setAxisScale(QwtPlot::xBottom,QDateTime::currentMSecsSinceEpoch(),QDateTime::currentMSecsSinceEpoch()+1000);
    m_pltMain->setAxisScale(QwtPlot::yLeft,m_dBaseLowY,m_dBaseUpY);    
}
//*********************************************     prepare     ********************************************// ok, perfect

//*********************************************     events      ********************************************//
void PlotPainter::mousePressEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton){
        m_qpntRbrPos=event->pos();
        m_dLowX =m_pltMain->invTransform(QwtPlot::xBottom,event->x());
        m_dUpY  =m_pltMain->invTransform(QwtPlot::yLeft,event->y());
        m_dUpX  =m_dLowX;
        m_dLowY =m_dUpY;
    };
    if(m_bZoom){
        m_rbrBRect->setGeometry(QRect(m_qpntRbrPos, QSize()));
        m_rbrBRect->show();
    }
    if(m_bMarker){
        int iIndex=0;
        iIndex=m_curveMain->closestPoint(m_pickerMain->trackerPosition());
        setMarker(m_curveMain->sample(iIndex));
        m_pltMain->replot();
    }
}

void PlotPainter::mouseReleaseEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton){
        m_dUpX=m_pltMain->invTransform(QwtPlot::xBottom,event->x());
        m_dLowY=m_pltMain->invTransform(QwtPlot::yLeft,event->y());
        if (m_bZoom){
                m_rbrBRect->hide();
            if((m_dLowX<m_dUpX)){
                changeYAxis(m_dLowY,m_dUpY);
                changeXAxis(m_dLowX,m_dUpX);
                m_dScrollUpX=m_dUpX;
                m_dScrollLowX=m_dLowX;
                refreshPlot();
            }
        };
        if ((!m_bZoom)&&(!m_bMarker)){
            scrollX(m_dLowX-m_dUpX);
            refreshPlot();
        };
    };    
    if ((event->button()==Qt::RightButton)&&(m_bZoom)){
        setYAxisToBase();
        setXAxisToBase();
        refreshPlot();
    };
}

void PlotPainter::mouseMoveEvent(QMouseEvent *event){
    if(m_bZoom){
            m_rbrBRect->setGeometry(QRect(m_qpntRbrPos, event->pos()).normalized());
    }
}
//*********************************************    //events      *******************************************//

//*********************************************    processing   ********************************************//
void PlotPainter::setMarker(QPointF pntSet){
    double dValY=pntSet.y();
    m_markerMain->setLabel(QString::number(dValY));
    m_markerMain->setValue(pntSet);
    m_markerMain->attach(m_pltMain);
}

void PlotPainter::setMarker(int iDataIndex){
    double dTme=m_vctdTime->value(iDataIndex);
    double dVal=m_vctdValue->value(iDataIndex);
    m_markerMain->setLabel(QString::number(dVal));
    m_markerMain->setValue(QPointF(dTme,dVal));
    m_markerMain->attach(m_pltMain);
    refreshPlot();
}

void PlotPainter::appendData(double dTime, double dValue){
    m_vctdTime->append(dTime);
    m_vctdValue->append(dValue);
}

void PlotPainter::setDataHolders(QVector<double> *vctTime, QVector<double> *vctValue){
    m_vctdTime=vctTime;
    m_vctdValue=vctValue;
    adjustXY();
}

void PlotPainter::adjustXY(){
    if((!m_vctdTime->isEmpty())&&(!m_vctdValue->isEmpty())){
        m_dScrollLowX=m_vctdTime->value(0);
        m_dScrollUpX=m_vctdTime->last();
        changeXAxis(m_dScrollLowX,m_dScrollUpX);
        changeYAxis(m_vctdValue->value(0),m_vctdValue->last());
    }else{
        changeYAxis(QDateTime::currentMSecsSinceEpoch(),QDateTime::currentMSecsSinceEpoch()+1000);
    }
}

void PlotPainter::adjustCurve(){
    m_curveMain->setSamples(*m_vctdTime,*m_vctdValue);
    m_curveMain->attach(m_pltMain);
}

void PlotPainter::getVectorData(){
    for(int i=0;i<m_vctdValue->count();i++){
        qDebug()<<m_vctdValue->at(i);
    }
}

void PlotPainter::refreshPlot(){
    adjustXY();
    adjustCurve();
    m_pltMain->replot();
}

void PlotPainter::clearPlot(){
    m_vctdTime->clear();
    m_vctdValue->clear();
    refreshPlot();
}

void PlotPainter::setPrinterData(QPrinter &printer){
    QwtPlotRenderer *renderPlot=new QwtPlotRenderer(m_pltMain);
    renderPlot->renderTo(m_pltMain,printer);
}

void PlotPainter::setPlotName(QString qstrName){
    m_pltMain->setTitle(qstrName);
}
//*********************************************    processing   ********************************************// ok, but slow

//***************************************     resizing,zoom etc...    **************************************//
double PlotPainter::getYLow(){
    return m_dBaseLowY;
}

double PlotPainter::getYUp(){
    return m_dBaseUpY;
}

void PlotPainter::scrollX(int dx){
    if((m_vctdTime->isEmpty())||(m_vctdValue->isEmpty()))return;
    m_dScrollLowX=m_dScrollLowX+dx;
    m_dScrollUpX=m_dScrollUpX+dx;
    changeXAxis(m_dScrollLowX,m_dScrollUpX);
}

void PlotPainter::setYAxis(double dLow, double dUp){
    m_dBaseUpY  =dUp;
    m_dBaseLowY =dLow;
    setYAxisToBase();
}

void PlotPainter::setYAxisToBase(){
    changeYAxis(m_dBaseLowY,m_dBaseUpY);
}

void PlotPainter::setXAxisToBase(){
    if((m_vctdTime->isEmpty())||(m_vctdValue->isEmpty())){
        m_dScrollUpX=QDateTime::currentMSecsSinceEpoch()+1000;
        m_dScrollLowX=QDateTime::currentMSecsSinceEpoch();
    }else{
        m_dScrollUpX=m_vctdTime->last();
        m_dScrollLowX=m_vctdTime->value(0);
    }
    changeXAxis(m_dScrollLowX, m_dScrollUpX);
}

void PlotPainter::changeYAxis(double dLow, double dUp){
    m_pltMain->setAxisScale(QwtPlot::yLeft,dLow,dUp);
}

void PlotPainter::changeXAxis(double dLow, double dUp){
    m_pltMain->setAxisScale(QwtPlot::xBottom,dLow,dUp);
}

void PlotPainter::onSelect(const QPointF &){
    // only for testing now
    qDebug()<<"selected";
}

void PlotPainter::resizePlot(int w, int h){
    if(w==0){w=MIN_PNL_WIDTH;}
    else{
        w=MIN_PNL_WIDTH+w;
    }
    resize(w,m_pltMain->height()+10);
    m_pltMain->resize(w,m_pltMain->height());
    m_pltMain->replot();
}
//***************************************     resizing,zoom etc...    **************************************//

//***************************************          other              **************************************//
void PlotPainter::enableObserver(){
    m_pickerMain=new QwtPlotPicker(m_pltMain->xBottom,m_pltMain->yLeft,
                                   QwtPlotPicker::HLineRubberBand, QwtPicker::AlwaysOn,m_pltMain->canvas());
    m_pickerMain->setStateMachine( new QwtPickerDragPointMachine() );
    m_pickerMain->setRubberBandPen(QColor(Qt::darkMagenta));    
    m_pickerMain->setTrackerPen(QColor(Qt::black));    
}

void PlotPainter::disableObserver(){
    m_pickerMain->setEnabled(false);
}

void PlotPainter::setCurveData(){
//
}

void PlotPainter::enableZoom(){
    m_bZoom=true;
}

void PlotPainter::disableZoom(){
    m_bZoom=false;
}

void PlotPainter::enableMarker(){
    if((m_vctdTime->isEmpty())||(m_vctdValue->isEmpty()))m_bMarker=false;
    else
        m_bMarker=true;
}

void PlotPainter::disableMarker(){
    m_bMarker=false;
}
//***************************************          other              **************************************//
