#include "widgets/cutwidget.h"
#include "ui_cutwidget.h"

CutWidget::CutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CutWidget)
{
    ui->setupUi(this);

    this->ui->progressBar->setDisabled(true);

    this->connect(this->ui->button_calculate, SIGNAL(clicked()), this, SLOT(reCalculateSerial()));
    this->connect(this->ui->button_calculate_parallel, SIGNAL(clicked()), this, SLOT(reCalculateParallel()));
    this->connect(this->ui->button_cancel, SIGNAL(clicked()), this, SLOT(cancelCalculation()));
    this->connect(&this->updateProgressTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    this->connect(&this->FutureWatcher, SIGNAL (finished()), this, SLOT (calculationFinished()));
    this->initPlot();
}

CutWidget::~CutWidget()
{
    delete ui;
}

void CutWidget::setParameters(CircuitParameters* parameters){
    this->parameters = parameters;
}


void CutWidget::updateGuiByParameters(){
    this->ui->value_c1->setText(QString::number(parameters->C1));
    this->ui->value_c2->setText(QString::number(parameters->C2));
    this->ui->value_l->setText(QString::number(parameters->L));
    this->ui->value_bp->setText(QString::number(parameters->Bp));
    this->ui->value_b0->setText(QString::number(parameters->B0));
    this->ui->value_r->setText(QString::number(parameters->R));
    this->ui->value_ro->setText(QString::number(parameters->ro));
    this->ui->value_i->setText(QString::number(parameters->I));
    this->ui->value_m0->setText(QString::number(parameters->m0));
    this->ui->value_m1->setText(QString::number(parameters->m1));
    this->ui->value_m2->setText(QString::number(parameters->m2));
    this->ui->value_tmax->setText(QString::number(parameters->t_max));
    this->ui->value_h0->setText(QString::number(parameters->h0));
    this->ui->value_ihmax->setText(QString::number(parameters->iStepMax));
    this->ui->value_uhmax->setText(QString::number(parameters->uStepMax));
}

void CutWidget::initPlot(){
    QCustomPlot* customPlot = this->ui->plot_cut;
    customPlot->xAxis->setLabel("u1");
    customPlot->yAxis->setLabel("u2");
    this->colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);

    colorMap->setGradient(QCPColorGradient::gpHot);
    colorMap->setAntialiased(false);
    colorMap->setInterpolate(false);
    colorMap->setDataRange(QCPRange(0,100));
}


void CutWidget::reCalculateSerial(){
    this->reCalculate(false);
}

void CutWidget::reCalculateParallel(){
    this->reCalculate(true);
}

void CutWidget::reCalculate(bool parallel){
    this->calculator = new TrajectoryCalculator(this->parameters);
    double u1Min = this->ui->input_u1_from->value();
    double u1Max = this->ui->input_u1_to->value();
    double u1Step = this->ui->input_u1_step->value();
    double u2Min = this->ui->input_u2_from->value();
    double u2Max = this->ui->input_u2_to->value();
    double u2Step = this->ui->input_u2_step->value();
    double i = this->ui->input_i->value();

    QFuture<CalculatedCut*> future;
    if(parallel){
        future = QtConcurrent::run(std::bind(&TrajectoryCalculator::parallelCalculateCut, this->calculator, u1Min, u1Max, u1Step, u2Min, u2Max, u2Step, i));
    }else{
        future = QtConcurrent::run(std::bind(&TrajectoryCalculator::calculateCut, this->calculator, u1Min, u1Max, u1Step, u2Min, u2Max, u2Step, i));
    }
    this->FutureWatcher.setFuture(future);
    this->clock.start();

    this->colorMap->data()->clear();
    this->ui->button_cancel->setEnabled(true);
    this->ui->button_calculate->setDisabled(true);
    this->ui->button_calculate_parallel->setDisabled(true);

    this->ui->time->setDisabled(false);
    this->ui->resultTable->setDisabled(true);
    this->ui->progressBar->setEnabled(true);

    this->updateProgressTimer.start(50);
    this->lastProgress = 0;

}

void CutWidget::cancelCalculation(){
    this->ui->progressBar->setValue(0);
    this->ui->progressBar->setDisabled(true);
    this->ui->button_cancel->setDisabled(true);
}

std::tuple<double, double, double> CutWidget::map(std::tuple<double, double, double> &parameters){
    double u1 = std::get<0>(parameters);
    double u2 = std::get<1>(parameters);
    double i = std::get<2>(parameters);

    TrajectoryResultType::ResultType result = this->calculator->calculateTrajectoryResult(i, u1, u2);
    QCPColorMap* colorMap = dynamic_cast<QCPColorMap*>(this->ui->plot_cut->plottable(0));
    switch(result){
        case TrajectoryResultType::CHA:
            colorMap->data()->setData(u1, u2, 0);
            break;
        case TrajectoryResultType::LC:
            colorMap->data()->setData(u1, u2, 50);
            break;
        case TrajectoryResultType::UNDETERMINED:
            colorMap->data()->setData(u1, u2, 100);
            break;
    }

    return parameters;
}


void CutWidget::calculationFinished(){
    int time = this->clock.elapsed();

    CalculatedCut* cut = this->FutureWatcher.result();
    this->updateProgressTimer.stop();

    this->ui->button_cancel->setDisabled(true);
    this->ui->button_calculate->setEnabled(true);
    this->ui->button_calculate_parallel->setEnabled(true);

    this->ui->progressBar->setValue(0);
    this->ui->progressBar->setDisabled(true);

    this->ui->time->setDisabled(true);
    this->ui->time->setText("0:00");


    this->initForCut(cut);
    this->reDraw(cut);

    this->updateResultTabe(cut, time);
    this->ui->resultTable->setEnabled(true);

    cut->writeToCSV("cut.txt");

    delete cut;
    delete this->calculator;
    this->calculator = NULL;
}

void CutWidget::initForCut(CalculatedCut* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;
    this->colorMap->data()->setSize(cut->u1Size, cut->u2Size);
    this->colorMap->data()->setRange(QCPRange(cut->u1Min, cut->u1Max), QCPRange(cut->u2Min, cut->u2Max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    customPlot->xAxis->setRange(cut->u1Min, cut->u1Max);
    customPlot->yAxis->setRange(cut->u2Min, cut->u2Max);
}

void CutWidget::reDraw(CalculatedCut* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;

    for (std::vector<std::vector<CalculatedCut::TrajectoryResult>>::const_iterator vector_iterator = cut->cbegin(); vector_iterator != cut->cend(); ++vector_iterator) {
        for (std::vector<CalculatedCut::TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            switch(result_iterator->result){
            case TrajectoryResultType::CHA:
                this->colorMap->data()->setData(result_iterator->u1, result_iterator->u2, 100);
                break;
            case TrajectoryResultType::LC:
                this->colorMap->data()->setData(result_iterator->u1, result_iterator->u2, 60);
                break;
            case TrajectoryResultType::UNDETERMINED:
                this->colorMap->data()->setData(result_iterator->u1, result_iterator->u2, 20);
                break;
            }
        }
    }

    customPlot->replot();
}

void CutWidget::reDrawPartial(PartiallyCalculatedCut* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;

    for (std::list<std::vector<CalculatedCut::TrajectoryResult>*>::const_iterator vector_iterator = cut->cbeginU1Columns(); vector_iterator != cut->cendU1Columns(); ++vector_iterator) {
        for (std::vector<CalculatedCut::TrajectoryResult>::const_iterator result_iterator = (*vector_iterator)->cbegin(); result_iterator != (*vector_iterator)->cend(); ++result_iterator) {
            switch(result_iterator->result){
            case TrajectoryResultType::CHA:
                this->colorMap->data()->setData(result_iterator->u1, result_iterator->u2, 100);
                break;
            case TrajectoryResultType::LC:
                this->colorMap->data()->setData(result_iterator->u1, result_iterator->u2, 60);
                break;
            case TrajectoryResultType::UNDETERMINED:
                this->colorMap->data()->setData(result_iterator->u1, result_iterator->u2, 20);
                break;
            }
        }
    }

    customPlot->replot();
}

void CutWidget::updateResultTabe(CalculatedCut* cut, int timeInMs){
    int chaosPoints = 0;
    int lcPoints = 0;
    int undPoints = 0;
    for (std::vector<std::vector<CalculatedCut::TrajectoryResult>>::const_iterator vector_iterator = cut->cbegin(); vector_iterator != cut->cend(); ++vector_iterator) {
        for (std::vector<CalculatedCut::TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            switch(result_iterator->result){
            case TrajectoryResultType::CHA:
                ++chaosPoints;
                break;
            case TrajectoryResultType::LC:
                ++lcPoints;
                break;
            case TrajectoryResultType::UNDETERMINED:
                ++undPoints;
                break;
            }
        }
    }

    QTableWidgetItem *resolution = new QTableWidgetItem;
    resolution->setText(QString("%1 x %2").arg(cut->u1Size).arg(cut->u2Size));

    QTableWidgetItem *time = new QTableWidgetItem;
    time->setText(this->formatTime(timeInMs));

    int allPoints = cut->u1Size * cut->u2Size;

    float chaosPercent = ((float)chaosPoints / (float)allPoints) * 100;
    QTableWidgetItem *chaos = new QTableWidgetItem;
    chaos->setText(QString("%1% (%2)").arg(chaosPercent, 0, 'f', 2).arg(chaosPoints));

    float lcPercent = ((float)lcPoints / (float)allPoints) * 100;
    QTableWidgetItem *lc = new QTableWidgetItem;
    lc->setText(QString("%1% (%2)").arg(lcPercent, 0, 'f', 2).arg(lcPoints));

    float undPercent = ((float)undPoints / (float)allPoints) * 100;
    QTableWidgetItem *und = new QTableWidgetItem;
    und->setText(QString("%1% (%2)").arg(undPercent, 0, 'f', 2).arg(undPoints));

    this->ui->resultTable->setItem(0,0, resolution);
    this->ui->resultTable->setItem(0,1, time);
    this->ui->resultTable->setItem(0,2, chaos);
    this->ui->resultTable->setItem(0,3, lc);
    this->ui->resultTable->setItem(0,4, und);
}

QString CutWidget::formatTime(int timeInMs){
    int elapsedMins = timeInMs/1000/60;
    int elapsedSeconds = timeInMs/1000 - std::floor(timeInMs/1000/60)*60;
    return QString("%1:%2").arg(elapsedMins).arg(elapsedSeconds,2, 10, QChar('0'));
}

void CutWidget::updateProgressBar()
{
    int elapsed = this->clock.elapsed();
    QString formattedTime = this->formatTime(elapsed);
    this->ui->time->setText(formattedTime);

    if(!this->calculator->hasPartialResult()){
        return;
    }

    PartiallyCalculatedCut* cut = this->calculator->partialResult();

    if(cut->progress() == this->lastProgress){
        return;
    }

    double rawProgress = cut->progress();
    int progress = std::round(rawProgress * 100);
    this->ui->progressBar->setValue(progress);

    this->initForCut(cut);
    this->reDrawPartial(cut);
    this->lastProgress = cut->progress();
}
