#include "trajectorywidget.h"

TrajectoryWidget::TrajectoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrajectoryWidget)
{
    ui->setupUi(this);

    this->connect(this->ui->button_calculate, SIGNAL(clicked()), this, SLOT(reCalculateAndReDraw()));
    this->connect(this->ui->button_animate, SIGNAL(clicked()), this, SLOT(reCalculateAndAnimate()));
    this->connect(this->ui->button_animate_stop, SIGNAL(clicked()), this, SLOT(stopAnimation()));


    // Update parameters if one of the inputs is changed
    this->connect(this->ui->input_C1, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_C2, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_L, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_Bp, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_B0, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_R, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_ro, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_I, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_m0, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_m1, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_m2, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_tmax, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_h0, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_ihmax, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_uhmax, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));
    this->connect(this->ui->input_n, SIGNAL(editingFinished()), this, SLOT(updateParametersByGui()));

    //TODO remove
    this->ui->input_i_0->setValue(0.000001);

    this->animationTimer = new QTimer(this);
    this->connect(this->animationTimer, &QTimer::timeout, this, &TrajectoryWidget::animationStep);

    this->initPlots();
}

TrajectoryWidget::~TrajectoryWidget()
{
    delete ui;
}

void TrajectoryWidget::updateParameters(CircuitParameters* parameters){
    this->updatingParameters = true;

    this->parameters = parameters;

    this->ui->input_C1->setValue(parameters->C1);
    this->ui->input_C2->setValue(parameters->C2);
    this->ui->input_L->setValue(parameters->L);
    this->ui->input_Bp->setValue(parameters->Bp);
    this->ui->input_B0->setValue(parameters->B0);
    this->ui->input_R->setValue(parameters->R);
    this->ui->input_ro->setValue(parameters->ro);
    this->ui->input_I->setValue(parameters->I);
    this->ui->input_m0->setValue(parameters->m0);
    this->ui->input_m1->setValue(parameters->m1);
    this->ui->input_m2->setValue(parameters->m2);
    this->ui->input_tmax->setValue(parameters->t_max);
    this->ui->input_h0->setValue(parameters->h0);
    this->ui->input_ihmax->setValue(parameters->iStepMax);
    this->ui->input_uhmax->setValue(parameters->uStepMax);
    this->ui->input_n->setValue(parameters->n);

    this->updatingParameters = false;
}

void TrajectoryWidget::updateParametersByGui(){
    if(this->updatingParameters){
        return;
    }

    this->parameters->C1 = this->ui->input_C1->value();
    this->parameters->C2 = this->ui->input_C2->value();
    this->parameters->L = this->ui->input_L->value();
    this->parameters->Bp = this->ui->input_Bp->value();
    this->parameters->B0 = this->ui->input_B0->value();
    this->parameters->R = this->ui->input_R->value();
    this->parameters->ro = this->ui->input_ro->value();
    this->parameters->I = this->ui->input_I->value();
    this->parameters->m0 = this->ui->input_m0->value();
    this->parameters->m1 = this->ui->input_m1->value();
    this->parameters->m2 = this->ui->input_m2->value();
    this->parameters->t_max = this->ui->input_tmax->value();
    this->parameters->h0 = this->ui->input_h0->value();
    this->parameters->iStepMax =this->ui->input_ihmax->value();
    this->parameters->uStepMax = this->ui->input_uhmax->value();
    this->parameters->n = this->ui->input_n->value();

    emit parametersChanged(this->parameters);
}

void TrajectoryWidget::initPlots(){
    QCustomPlot* iu1Plot = ui->plot_iu1;
    QCPCurve *iu1Curve = new QCPCurve(iu1Plot->xAxis, iu1Plot->yAxis);
    iu1Plot->setInteraction(QCP::iRangeDrag, true);
    //iu1Plot->setInteraction(QCP::iRangeZoom, true);
    iu1Plot->addPlottable(iu1Curve);
    QCPGraph *iu1StartPoint = new QCPGraph(iu1Plot->xAxis, iu1Plot->yAxis);
    iu1Plot->addPlottable(iu1StartPoint);
    iu1StartPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    iu1StartPoint->setPen(QPen(QColor(16,192,16)));
    QCPGraph *iu1EndPoint = new QCPGraph(iu1Plot->xAxis, iu1Plot->yAxis);
    iu1Plot->addPlottable(iu1EndPoint);
    iu1EndPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    iu1EndPoint->setPen(QPen(QColor(192,16,16)));
    iu1Plot->xAxis->setLabel("u1");
    iu1Plot->yAxis->setLabel("i");
    this->connect(iu1Plot, &QCustomPlot::mouseDoubleClick, this, &TrajectoryWidget::resetPlots);
    this->connect(iu1Plot, &QCustomPlot::mouseWheel, this, &TrajectoryWidget::zoomPlot);
    this->connect(iu1Plot, SIGNAL(afterReplot()), this, SLOT(synchronizeRangeWithIU1()));

    QCustomPlot* iu2Plot = ui->plot_iu2;
    QCPCurve *iu2Curve = new QCPCurve(iu2Plot->xAxis, iu2Plot->yAxis);
    iu2Plot->setInteraction(QCP::iRangeDrag, true);
    //iu2Plot->setInteraction(QCP::iRangeZoom, true);
    iu2Plot->addPlottable(iu2Curve);
    QCPGraph *iu2StartPoint = new QCPGraph(iu2Plot->xAxis, iu2Plot->yAxis);
    iu2Plot->addPlottable(iu2StartPoint);
    iu2StartPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    iu2StartPoint->setPen(QPen(QColor(16,192,16)));
    QCPGraph *iu2EndPoint = new QCPGraph(iu2Plot->xAxis, iu2Plot->yAxis);
    iu2Plot->addPlottable(iu2EndPoint);
    iu2EndPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    iu2EndPoint->setPen(QPen(QColor(192,16,16)));
    iu2Plot->xAxis->setLabel("u2");
    iu2Plot->yAxis->setLabel("i");
    this->connect(iu2Plot, &QCustomPlot::mouseDoubleClick, this, &TrajectoryWidget::resetPlots);
    this->connect(iu2Plot, &QCustomPlot::mouseWheel, this, &TrajectoryWidget::zoomPlot);
    this->connect(iu2Plot, SIGNAL(afterReplot()), this, SLOT(synchronizeRangeWithIU2()));

    QCustomPlot* u1u2Plot = ui->plot_u1u2;
    QCPCurve *u1u2Curve = new QCPCurve(u1u2Plot->xAxis, u1u2Plot->yAxis);
    u1u2Plot->setInteraction(QCP::iRangeDrag, true);
    //u1u2Plot->setInteraction(QCP::iRangeZoom, true);
    u1u2Plot->addPlottable(u1u2Curve);
    QCPGraph *u1u2StartPoint = new QCPGraph(u1u2Plot->xAxis, u1u2Plot->yAxis);
    u1u2Plot->addPlottable(u1u2StartPoint);
    u1u2StartPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    u1u2StartPoint->setPen(QPen(QColor(16,192,16)));
    QCPGraph *u1u2EndPoint = new QCPGraph(u1u2Plot->xAxis, u1u2Plot->yAxis);
    u1u2Plot->addPlottable(u1u2EndPoint);
    u1u2EndPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossCircle, 10));
    u1u2EndPoint->setPen(QPen(QColor(192,16,16)));
    u1u2Plot->xAxis->setLabel("u1");
    u1u2Plot->yAxis->setLabel("u2");
    this->connect(u1u2Plot, &QCustomPlot::mouseDoubleClick, this, &TrajectoryWidget::resetPlots);
    this->connect(u1u2Plot, &QCustomPlot::mouseWheel, this, &TrajectoryWidget::zoomPlot);
    this->connect(u1u2Plot, SIGNAL(afterReplot()), this, SLOT(synchronizeRangeWithU1U2()));
}

void TrajectoryWidget::redrawPlot(QCustomPlot* plot, Trajectory* result, int xRange, int yRange ){
     QCPCurve* curve = dynamic_cast<QCPCurve*>(plot->plottable(0));
     QCPGraph* startPoint = dynamic_cast<QCPGraph*>(plot->plottable(1));
     QCPGraph* endPoint = dynamic_cast<QCPGraph*>(plot->plottable(2));
     curve->clearData();

     const std::vector<Point3DT>* points = result->points;



     if(plot == this->ui->plot_iu1){
         for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
             if(point == points->begin()){
                 startPoint->data()->clear();
                 startPoint->addData(point->u1, point->i);
             }
             curve->addData(point->t, point->u1, point->i);
             if(point == points->end() -1 ){
                 endPoint->data()->clear();
                 endPoint->addData(point->u1, point->i);
             }
         }
     }else if(plot == this->ui->plot_iu2){
         for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
             if(point == points->begin()){
                 startPoint->data()->clear();
                 startPoint->addData(point->u2, point->i);
             }
             curve->addData(point->t, point->u2, point->i);
             if(point == points->end() -1 ){
                 endPoint->data()->clear();
                 endPoint->addData(point->u2, point->i);
             }
         }
     }else if(plot == this->ui->plot_u1u2){
         for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
             if(point == points->begin()){
                 startPoint->data()->clear();
                 startPoint->addData(point->u1, point->u2);
             }
             curve->addData(point->t, point->u1, point->u2);
             if(point == points->end() -1 ){
                 endPoint->data()->clear();
                 endPoint->addData(point->u1, point->u2);
             }
         }
     }


     plot->xAxis->setRange(-xRange,xRange);
     plot->yAxis->setRange(-yRange,yRange);
     plot->replot();
}

void TrajectoryWidget::redrawPlots(Trajectory* result){
    Point3DT maxMins = result->getMaxMins();

    int iMaxMin = std::ceil(maxMins.i) + 1;
    int uMaxMin = std::max(std::ceil(maxMins.u1), std::ceil(maxMins.u2)) +1 ;

    this->redrawPlot(this->ui->plot_iu1, result, uMaxMin, iMaxMin);
    this->redrawPlot(this->ui->plot_iu2, result, uMaxMin, iMaxMin);
    this->redrawPlot(this->ui->plot_u1u2, result, uMaxMin, uMaxMin);
}

void TrajectoryWidget::zoomPlot(QWheelEvent* event){
 float factor = 1 - (event->delta() * 0.002);

 QCPRange rangeU1 = this->ui->plot_iu1->xAxis->range();
 QCPRange rangeU2 = this->ui->plot_iu2->xAxis->range();
 QCPRange rangeI = this->ui->plot_iu1->yAxis->range();

 this->ui->plot_iu1->xAxis->setRange(rangeU1.lower*factor, rangeU1.upper*factor);
 this->ui->plot_iu1->yAxis->setRange(rangeI.lower*factor, rangeI.upper*factor);

 this->ui->plot_iu2->xAxis->setRange(rangeU2.lower*factor, rangeU2.upper*factor);
 this->ui->plot_iu2->yAxis->setRange(rangeI.lower*factor, rangeI.upper*factor);

 this->ui->plot_u1u2->xAxis->setRange(rangeU1.lower*factor, rangeU1.upper*factor);
 this->ui->plot_u1u2->yAxis->setRange(rangeU2.lower*factor, rangeU2.upper*factor);

 this->ui->plot_iu1->replot();
 this->ui->plot_iu2->replot();
 this->ui->plot_u1u2->replot();

}


void TrajectoryWidget::synchronizeRangeWithIU1(){
    QCPRange rangeU1 = this->ui->plot_iu1->xAxis->range();
    QCPRange rangeI = this->ui->plot_iu1->yAxis->range();

    QCustomPlot * iu2 = this->ui->plot_iu2;
    QCustomPlot * u1u2 = this->ui->plot_u1u2;

    if(iu2->yAxis->range() != rangeI){
        iu2->yAxis->setRange(rangeI);
        iu2->replot();
    }

    if(u1u2->yAxis->range() != rangeU1){
        u1u2->xAxis->setRange(rangeU1);
        u1u2->replot();
    }
}

void TrajectoryWidget::synchronizeRangeWithIU2(){
    QCPRange rangeU2 = this->ui->plot_iu2->xAxis->range();
    QCPRange rangeI = this->ui->plot_iu2->yAxis->range();

    QCustomPlot * iu1 = this->ui->plot_iu1;
    QCustomPlot * u1u2 = this->ui->plot_u1u2;

    if(iu1->yAxis->range() != rangeI){
        iu1->yAxis->setRange(rangeI);
        iu1->replot();
    }

    if(u1u2->yAxis->range() != rangeU2){
        u1u2->yAxis->setRange(rangeU2);
        u1u2->replot();
    }
}

void TrajectoryWidget::synchronizeRangeWithU1U2(){
    QCPRange rangeU1 = this->ui->plot_u1u2->xAxis->range();
    QCPRange rangeU2 = this->ui->plot_u1u2->yAxis->range();

    QCustomPlot * iu1 = this->ui->plot_iu1;
    QCustomPlot * iu2 = this->ui->plot_iu2;

    if(iu1->xAxis->range() != rangeU1){
        iu1->xAxis->setRange(rangeU1);
        iu1->replot();
    }

    if(iu2->xAxis->range() != rangeU2){
        iu2->xAxis->setRange(rangeU2);
        iu2->replot();
    }
}

void TrajectoryWidget::resetPlots(QMouseEvent* event){
    Point3DT maxMins = this->currentResult->getMaxMins();
    int iMaxMin = std::ceil(maxMins.i) + 1;
    int uMaxMin = std::max(std::ceil(maxMins.u1), std::ceil(maxMins.u2)) +1 ;

    this->ui->plot_iu1->xAxis->setRange(-uMaxMin,uMaxMin);
    this->ui->plot_iu1->yAxis->setRange(-iMaxMin,iMaxMin);

    this->ui->plot_iu2->xAxis->setRange(-uMaxMin,uMaxMin);
    this->ui->plot_iu2->yAxis->setRange(-iMaxMin,iMaxMin);

    this->ui->plot_u1u2->xAxis->setRange(-uMaxMin,uMaxMin);
    this->ui->plot_u1u2->yAxis->setRange(-uMaxMin,uMaxMin);


    this->ui->plot_iu1->replot();
    this->ui->plot_iu2->replot();
    this->ui->plot_u1u2->replot();
}

void TrajectoryWidget::redrawResultTabe(Trajectory* result, int time){
    QTableWidgetItem *points = new QTableWidgetItem;

    points->setText(QString::number(result->points->size()));

    QTableWidgetItem *divisions = new QTableWidgetItem;
    divisions->setText(QString::number(result->divisionCount));

    QTableWidgetItem *type = new QTableWidgetItem;
    type->setText(QString("%1 ms").arg(time));

    this->ui->resultTable->setItem(0,0, points);
    this->ui->resultTable->setItem(0,1, divisions);
    this->ui->resultTable->setItem(0,2, type);
}

void TrajectoryWidget::stopAnimation(){
    this->animationTimer->stop();
}

void TrajectoryWidget::animatePlots(){
    Point3DT maxMins = this->currentResult->getMaxMins();

    int iMaxMin = std::ceil(maxMins.i) + 1;
    int uMaxMin = std::max(std::ceil(maxMins.u1), std::ceil(maxMins.u2)) +1 ;

    this->ui->plot_iu1->xAxis->setRange(-uMaxMin,uMaxMin);
    this->ui->plot_iu1->yAxis->setRange(-iMaxMin,iMaxMin);
    QCPCurve* iu1curve = dynamic_cast<QCPCurve*>(this->ui->plot_iu1->plottable(0));
    iu1curve->clearData();

    this->ui->plot_iu2->xAxis->setRange(-uMaxMin,uMaxMin);
    this->ui->plot_iu2->yAxis->setRange(-iMaxMin,iMaxMin);
    QCPCurve* iu2curve = dynamic_cast<QCPCurve*>(this->ui->plot_iu2->plottable(0));
    iu2curve->clearData();

    this->ui->plot_u1u2->xAxis->setRange(-uMaxMin,uMaxMin);
    this->ui->plot_u1u2->yAxis->setRange(-uMaxMin,uMaxMin);
    QCPCurve* u1u2curve = dynamic_cast<QCPCurve*>(this->ui->plot_u1u2->plottable(0));
    u1u2curve->clearData();

    this->nextAnimationPoint = this->currentResult->points->begin();
    this->animationStart = QDateTime::currentMSecsSinceEpoch();
    this->animationTimer->start(33);
}

void TrajectoryWidget::animationStep(){
    if(this->nextAnimationPoint == this->currentResult->points->end()){
        this->stopAnimation();
        return;
    }

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    int timerDiff = now - this->animationStart;

    QCPCurve* iu1curve = dynamic_cast<QCPCurve*>(this->ui->plot_iu1->plottable(0));
    QCPCurve* iu2curve = dynamic_cast<QCPCurve*>(this->ui->plot_iu2->plottable(0));
    QCPCurve* u1u2curve = dynamic_cast<QCPCurve*>(this->ui->plot_u1u2->plottable(0));

    while(this->nextAnimationPoint != this->currentResult->points->end() && timerDiff >= this->nextAnimationPoint->t * 100){
        iu1curve->addData(this->nextAnimationPoint->t, this->nextAnimationPoint->u1, this->nextAnimationPoint->i);
        iu2curve->addData(this->nextAnimationPoint->t, this->nextAnimationPoint->u2, this->nextAnimationPoint->i);
        u1u2curve->addData(this->nextAnimationPoint->t, this->nextAnimationPoint->u1, this->nextAnimationPoint->u2);
        this->nextAnimationPoint++;
    }

    this->ui->plot_iu1->replot();
    this->ui->plot_iu2->replot();
    this->ui->plot_u1u2->replot();
}



int TrajectoryWidget::reCalculate(){
    if(this->currentResult != NULL){
        delete this->currentResult;
        this->currentResult = NULL;
    }
    QTime clock;
    clock.start();
    TrajectoryCalculator calculator = TrajectoryCalculator(this->parameters);

    this->currentResult = calculator.calculateTrajectory(this->ui->input_i_0->value(), this->ui->input_u1_0->value(), this->ui->input_u2_0->value());
    return clock.elapsed();
}

void TrajectoryWidget::reCalculateAndReDraw(){
    this->stopAnimation();
    int time = this->reCalculate();
    this->redrawPlots(this->currentResult);
    this->redrawResultTabe(this->currentResult, time);
}

void TrajectoryWidget::reCalculateAndAnimate(){
    this->stopAnimation();
    this->reCalculate();
    this->animatePlots();
}
