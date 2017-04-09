#include "widgets/crosssectionwidget.h"
#include "ui_crosssectionwidget.h"

CrossSectionWidget::CrossSectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossSectionWidget)
{
    ui->setupUi(this);

    this->ui->progressBar->setDisabled(true);
    this->ui->resultTable->horizontalHeader()->hide();

    this->calculatButtonSignalMapper = new QSignalMapper(this);

    this->connect(this->calculatButtonSignalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(calculateButtonPressed(QWidget*)));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_u1i, this->ui->button_calculate_u1i);
    this->connect(this->ui->button_calculate_u1i, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_parallel_u1i, this->ui->button_calculate_parallel_u1i);
    this->connect(this->ui->button_calculate_parallel_u1i, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_u2i, this->ui->button_calculate_u2i);
    this->connect(this->ui->button_calculate_u2i, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_parallel_u2i, this->ui->button_calculate_parallel_u2i);
    this->connect(this->ui->button_calculate_parallel_u2i, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_u1u2, this->ui->button_calculate_u1u2);
    this->connect(this->ui->button_calculate_u1u2, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_parallel_u1u2, this->ui->button_calculate_parallel_u1u2);
    this->connect(this->ui->button_calculate_parallel_u1u2, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->connect(this->ui->button_cancel_u1i, SIGNAL(clicked()), this, SLOT(cancelCalculation()));
    this->connect(this->ui->button_cancel_u2i, SIGNAL(clicked()), this, SLOT(cancelCalculation()));
    this->connect(this->ui->button_cancel_u1u2, SIGNAL(clicked()), this, SLOT(cancelCalculation()));

    this->connect(&this->updateProgressTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    this->connect(&this->FutureWatcher, SIGNAL (finished()), this, SLOT (calculationFinished()));

    this->connect(this->ui->plot_cut, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    this->initPlot();
}

CrossSectionWidget::~CrossSectionWidget()
{
    delete ui;
    delete parameters;
    delete calculator;
    delete colorMap;
    delete calculatButtonSignalMapper;
}

void CrossSectionWidget::updateParameters(CircuitParameters* parameters){
    this->parameters = parameters;

    this->ui->circuitparameters->setParameters(parameters);
}

void CrossSectionWidget::saveCurrentResultToPng()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export to PNG"), QString(), QString("PNG files (*.png)"));

    if(fileName.isEmpty()){
        return;
    }

    this->ui->plot_cut->savePng(fileName, 0, 0, 3, -1);
}

void CrossSectionWidget::exportCurrentResultToTxt()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export to TXT"), QString(), QString("Text files (*.txt)"));

    if(fileName.isEmpty()){
        return;
    }

    this->currentResult->writeToTxt(fileName.toStdString(), "\t");
}

void CrossSectionWidget::exportCurrentResultToCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export to CSV"), QString(), QString("Comma-separated values (*.csv)"));

    if(fileName.isEmpty()){
        return;
    }

    this->currentResult->writeToTxt(fileName.toStdString(), ",");
}

void CrossSectionWidget::exportUndeterminedToTxt()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export undetermined points to TXT"), QString(), QString("Text files (*.txt)"));

    if(fileName.isEmpty()){
        return;
    }

    this->currentResult->writeToTxt(fileName.toStdString(), "\t", false, true);
}

void CrossSectionWidget::exportUndeterminedToCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export undetermined points to CSV"), QString(), QString("Comma-separated values (*.csv)"));

    if(fileName.isEmpty()){
        return;
    }

    this->currentResult->writeToTxt(fileName.toStdString(), ",", false, true);
}



void CrossSectionWidget::contextMenuRequest(QPoint pos)
{
    if(this->currentResult != NULL){
        QMenu *menu = new QMenu(this);
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->addAction("Export to CSV", this, SLOT(exportCurrentResultToCsv()));
        menu->addAction("Export undetermined points to CSV", this, SLOT(exportUndeterminedToCsv()));
        menu->addAction("Export to TXT", this, SLOT(exportCurrentResultToTxt()));
        menu->addAction("Export undetermined points to TXT", this, SLOT(exportUndeterminedToTxt()));
        menu->addAction("Export to PNG", this, SLOT(saveCurrentResultToPng()));
        menu->popup(ui->plot_cut->mapToGlobal(pos));
    }
}

void CrossSectionWidget::initPlot(){
    QCustomPlot* customPlot = this->ui->plot_cut;
    QFont font = customPlot->xAxis->labelFont();
    font.setPointSize(11);
    customPlot->xAxis->setLabelFont(font);
    customPlot->yAxis->setLabelFont(font);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    this->colorMap = new CrossSectionMap(customPlot->xAxis, customPlot->yAxis);

    //colorMap->setGradient(QCPColorGradient::gpHot);
    colorMap->setAntialiased(false);
    colorMap->setInterpolate(false);
}

void CrossSectionWidget::calculateButtonPressed(QWidget* button){
    if(button == ui->button_calculate_u1i){
        this->reCalculate(I_U1, false);
    }else if(button == ui->button_calculate_parallel_u1i){
        this->reCalculate(I_U1, true);
    }else if(button == ui->button_calculate_u2i){
        this->reCalculate(I_U2, false);
    }else if(button == ui->button_calculate_parallel_u2i){
        this->reCalculate(I_U2, true);
    }else if(button == ui->button_calculate_u1u2){
        this->reCalculate(U2_U1, false);
    }else if(button == ui->button_calculate_parallel_u1u2){
        this->reCalculate(U2_U1, true);
    }
}

void CrossSectionWidget::reCalculate(CrossSectionType type, bool parallel){
    this->calculator = new TrajectoryCalculator(this->parameters);

    double xMin, xMax, xPoints, yMin, yMax, yPoints, z;
    switch (type) {
    case I_U1:
        xMin = this->ui->input_u1_from_u1i->value();
        xMax = this->ui->input_u1_to_u1i->value();
        xPoints = this->ui->input_u1_points_u1i->value();
        yMin = this->ui->input_i_from_u1i->value();
        yMax = this->ui->input_i_to_u1i->value();
        yPoints = this->ui->input_i_points_u1i->value();
        z = this->ui->input_u2_u1i->value();

        this->ui->button_cancel_u1i->setEnabled(true);
        break;
    case I_U2:
        xMin = this->ui->input_u2_from_u2i->value();
        xMax = this->ui->input_u2_to_u2i->value();
        xPoints = this->ui->input_u2_points_u2i->value();
        yMin = this->ui->input_i_from_u2i->value();
        yMax = this->ui->input_i_to_u2i->value();
        yPoints = this->ui->input_i_points_u2i->value();
        z = this->ui->input_u1_u2i->value();

        this->ui->button_cancel_u2i->setEnabled(true);
        break;
    case U2_U1:
        xMin = this->ui->input_u1_from_u1u2->value();
        xMax = this->ui->input_u1_to_u1u2->value();
        xPoints = this->ui->input_u1_points_u1u2->value();
        yMin = this->ui->input_u2_from_u1u2->value();
        yMax = this->ui->input_u2_to_u1u2->value();
        yPoints = this->ui->input_u2_points_u1u2->value();
        z = this->ui->input_i_u1u2->value();

        this->ui->button_cancel_u1u2->setEnabled(true);
        break;
    }


    std::vector<TrajectoryTest>* tests = this->ui->test->getTests();
    QFuture<CalculatedCrossSection*> future;
    if(parallel){
        future = QtConcurrent::run(std::bind(&TrajectoryCalculator::parallelCalculateCrossSection, this->calculator, type, xMin, xMax, xPoints, yMin, yMax, yPoints, z, tests));
    }else{
        future = QtConcurrent::run(std::bind(&TrajectoryCalculator::calculateCrossSection, this->calculator, type, xMin, xMax, xPoints, yMin, yMax, yPoints, z, tests));
    }

    this->FutureWatcher.setFuture(future);
    this->clock.start();

    this->colorMap->data()->clear();
    this->colorMap->updateColors(tests);

    this->ui->button_calculate_u1i->setDisabled(true);
    this->ui->button_calculate_parallel_u1i->setDisabled(true);
    this->ui->button_calculate_u2i->setDisabled(true);
    this->ui->button_calculate_parallel_u2i->setDisabled(true);
    this->ui->button_calculate_u1u2->setDisabled(true);
    this->ui->button_calculate_parallel_u1u2->setDisabled(true);

    this->ui->time->setDisabled(false);
    this->ui->resultTable->setDisabled(true);
    this->ui->progressBar->setEnabled(true);

    this->ui->plot_cut->setInteraction(QCP::iRangeDrag, false);
    this->ui->plot_cut->setInteraction(QCP::iRangeZoom, false);

    this->updateProgressTimer.start(250);
    this->lastProgress = 0;

    if(this->currentResult != NULL){
        delete this->currentResult;
    }
    this->currentResult = NULL;

}

void CrossSectionWidget::cancelCalculation(){
    this->ui->progressBar->setValue(0);
    this->ui->progressBar->setDisabled(true);

    this->ui->button_cancel_u1i->setDisabled(true);
    this->ui->button_cancel_u2i->setDisabled(true);
    this->ui->button_cancel_u1u2->setDisabled(true);
    this->ui->button_calculate_u1i->setEnabled(true);

    this->ui->button_calculate_parallel_u1i->setEnabled(true);
    this->ui->button_calculate_u2i->setEnabled(true);
    this->ui->button_calculate_parallel_u2i->setEnabled(true);
    this->ui->button_calculate_u1u2->setEnabled(true);
    this->ui->button_calculate_parallel_u1u2->setEnabled(true);

    this->calculator->cancelled = true;
    this->updateProgressTimer.stop();

}

void CrossSectionWidget::calculationFinished(){
    int time = this->clock.elapsed();

    CalculatedCrossSection* cut = this->FutureWatcher.result();
    this->updateProgressTimer.stop();

    this->ui->button_cancel_u1i->setDisabled(true);
    this->ui->button_cancel_u2i->setDisabled(true);
    this->ui->button_cancel_u1u2->setDisabled(true);
    this->ui->button_calculate_u1i->setEnabled(true);

    this->ui->button_calculate_parallel_u1i->setEnabled(true);
    this->ui->button_calculate_u2i->setEnabled(true);
    this->ui->button_calculate_parallel_u2i->setEnabled(true);
    this->ui->button_calculate_u1u2->setEnabled(true);
    this->ui->button_calculate_parallel_u1u2->setEnabled(true);

    this->ui->progressBar->setValue(0);
    this->ui->progressBar->setDisabled(true);

    this->ui->time->setDisabled(true);
    this->ui->time->setText(Utils::formatTime(0));


    this->initForCut(cut);
    this->reDraw(cut);

    this->ui->plot_cut->setInteraction(QCP::iRangeDrag, true);
    this->ui->plot_cut->setInteraction(QCP::iRangeZoom, true);

    this->updateResultTable(cut, time);
    this->ui->resultTable->setEnabled(true);

    if(this->currentResult != NULL){
        delete this->currentResult;
    }

    this->currentResult = cut;
    delete this->calculator;
    this->calculator = NULL;
}


void CrossSectionWidget::initForCut(CalculatedCrossSection* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;
    if(cut->type == I_U1){
        customPlot->xAxis->setLabel("u1 [V]");
        customPlot->yAxis->setLabel("i [A]");
    }else if(cut->type == I_U2){
        customPlot->xAxis->setLabel("u2 [V]");
        customPlot->yAxis->setLabel("i [A]");
    }else if(cut->type == U2_U1){
        customPlot->xAxis->setLabel("u1 [V]");
        customPlot->yAxis->setLabel("u2 [V]");
    }

    this->colorMap->data()->setSize(cut->columnCount, cut->rowCount);
    this->colorMap->data()->setRange(QCPRange(cut->columnMin, cut->columnMax), QCPRange(cut->rowMin, cut->rowMax)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    customPlot->xAxis->setRange(cut->columnMin, cut->columnMax);
    customPlot->yAxis->setRange(cut->rowMin, cut->rowMax);
}

void CrossSectionWidget::reDraw(CalculatedCrossSection* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = cut->cbegin(); vector_iterator != cut->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            this->colorMap->data()->setData(result_iterator->column, result_iterator->row, cut->getTestIndex(result_iterator->test));
        }
    }

    for(std::vector<TrajectoryTest>::const_iterator test = cut->cbeginTests(); test != cut->cendTests(); ++test){
        if(test->isChaos()){
            QCPItemRect* rect = new QCPItemRect(customPlot);
            QPen pen = QPen(QColor(0,0,0));
            pen.setWidth(2);
            rect->setPen(pen);
            customPlot->addItem(rect);
            rect->topLeft->setCoords(test->u1Lo, test->iHi);
            rect->bottomRight->setCoords(test->u1Hi, test->iLo);

            //rect->pen().setColor(QColor(32,32,224));
        }
    }

    customPlot->replot();
}

void CrossSectionWidget::reDrawPartial(PartiallyCalculatedCrossSection* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;

    for (std::list<std::vector<TrajectoryResult>*>::const_iterator vector_iterator = cut->cbeginColumns(); vector_iterator != cut->cendColumns(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = (*vector_iterator)->cbegin(); result_iterator != (*vector_iterator)->cend(); ++result_iterator) {
            this->colorMap->data()->setData(result_iterator->column, result_iterator->row, cut->getTestIndex(result_iterator->test));
        }
    }

    for(std::vector<TrajectoryTest>::const_iterator test = cut->cbeginTests(); test != cut->cendTests(); ++test){
        if(test->isChaos()){
            QCPItemRect* rect = new QCPItemRect(customPlot);
            QPen pen = QPen(QColor(0,0,0));
            pen.setWidth(2);
            rect->setPen(pen);
            customPlot->addItem(rect);
            rect->topLeft->setCoords(test->u1Lo, test->iHi);
            rect->bottomRight->setCoords(test->u1Hi, test->iLo);

            //rect->pen().setColor(QColor(32,32,224));
        }
    }

    customPlot->replot();
}

void CrossSectionWidget::updateResultTable(CalculatedCrossSection* cut, int timeInMs){
    int chaosPoints = 0;
    int lcPoints = 0;
    int undPoints = 0;
    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = cut->cbegin(); vector_iterator != cut->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            switch(result_iterator->result()){
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
    resolution->setText(QString("%1 x %2").arg(cut->columnCount).arg(cut->rowCount));

    QTableWidgetItem *time = new QTableWidgetItem;
    time->setText(Utils::formatTime(timeInMs));

    int allPoints = cut->columnCount * cut->rowCount;

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

void CrossSectionWidget::updateProgressBar()
{
    if(this->calculator->cancelled){
        return;
    }

    int elapsed = this->clock.elapsed();
    QString formattedTime = Utils::formatTime(elapsed);
    this->ui->time->setText(formattedTime);

    if(!this->calculator->hasPartialResult()){
        return;
    }

    PartiallyCalculatedCrossSection* cut = this->calculator->partialResult();

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
