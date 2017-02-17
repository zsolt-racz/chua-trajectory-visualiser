#include "widgets/csseriewidget.h"
#include "ui_csseriewidget.h"

CsSerieWidget::CsSerieWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CsSerieWidget)
{
    ui->setupUi(this);

    this->connect(this->ui->folder_button, SIGNAL(clicked()), this, SLOT(selectWorkingDirAction()));

    this->calculatButtonSignalMapper = new QSignalMapper(this);

    this->connect(this->calculatButtonSignalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(calculateButtonPressed(QWidget*)));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate, this->ui->button_calculate);
    this->connect(this->ui->button_calculate, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->calculatButtonSignalMapper->setMapping(this->ui->button_calculate_parallel, this->ui->button_calculate_parallel);
    this->connect(this->ui->button_calculate_parallel, SIGNAL(clicked()), this->calculatButtonSignalMapper, SLOT(map()));

    this->connect(&this->updateProgressTimer, SIGNAL(timeout()), this, SLOT(updateProgress()));
    this->connect(this->ui->button_stop, SIGNAL(clicked()), this, SLOT(cancelCalculation()));
    this->connect(this->ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*, QListWidgetItem*)));

    this->connect(&this->FutureWatcher, SIGNAL (finished()), this, SLOT (csCalculationFinished()));
    this->connect(this->ui->plot_cut, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

CsSerieWidget::~CsSerieWidget()
{
    delete colorMap;
    delete ui;
}


void CsSerieWidget::updateParameters(CircuitParameters* parameters){
    this->parameters = parameters;

    this->ui->circuitparameters->setParameters(parameters);
}

void CsSerieWidget::setTestTable(TestInputWidget* table){
    this->table = table;
}


void CsSerieWidget::selectWorkingDirAction(){
    QString dirName = QFileDialog::getExistingDirectory(this, QString("Select directory"), QString());

    if(dirName.isEmpty()){
        return;
    }

    this->workingDir = dirName;
    this->ui->folder_label->setText(dirName);
    this->ui->button_calculate->setEnabled(true);
    this->ui->button_calculate_parallel->setEnabled(true);

    // If info.txt does not exist
    this->ui->input_i_from->setEnabled(true);
    this->ui->input_i_to->setEnabled(true);
    this->ui->input_i_step->setEnabled(true);
    this->ui->input_u1_from->setEnabled(true);
    this->ui->input_u1_to->setEnabled(true);
    this->ui->input_u1_step->setEnabled(true);
    this->ui->input_u2_from->setEnabled(true);
    this->ui->input_u2_to->setEnabled(true);
    this->ui->input_u2_step->setEnabled(true);

    this->updateCsList();
    this->initPlot();
}

void CsSerieWidget::initPlot(){
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

void CsSerieWidget::initForCut(CalculatedCut* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;
    if(cut->type == I_U1){
        customPlot->xAxis->setLabel("u1");
        customPlot->yAxis->setLabel("i");
    }else if(cut->type == I_U2){
        customPlot->xAxis->setLabel("u2");
        customPlot->yAxis->setLabel("i");
    }else if(cut->type == U2_U1){
        customPlot->xAxis->setLabel("u1");
        customPlot->yAxis->setLabel("u2");
    }

    this->colorMap->data()->setSize(cut->xSize, cut->ySize);
    this->colorMap->data()->setRange(QCPRange(cut->xMin, cut->xMax), QCPRange(cut->yMin, cut->yMax)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    customPlot->xAxis->setRange(cut->xMin, cut->xMax);
    customPlot->yAxis->setRange(cut->yMin, cut->yMax);
}

void CsSerieWidget::draw(CalculatedCut* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = cut->cbegin(); vector_iterator != cut->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            this->colorMap->data()->setData(result_iterator->x, result_iterator->y, cut->getTestIndex(result_iterator->test));
        }
    }

    customPlot->replot();
}

void CsSerieWidget::saveCurrentResultToPng()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export to PNG"), QString(), QString("PNG files (*.png)"));

    if(fileName.isEmpty()){
        return;
    }

    this->ui->plot_cut->savePng(fileName, 0, 0, 1.2, -1);
}

void CsSerieWidget::exportCurrentResultToTxt()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Expor to TXT"), QString(), QString("Text files (*.txt)"));

    if(fileName.isEmpty()){
        return;
    }

    this->currentResult->writeToTxt(fileName.toStdString(), "\t");
}

void CsSerieWidget::exportCurrentResultToCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export to CSV"), QString(), QString("Comma-separated values (*.csv)"));

    if(fileName.isEmpty()){
        return;
    }

    this->currentResult->writeToTxt(fileName.toStdString(), ",");
}


void CsSerieWidget::contextMenuRequest(QPoint pos)
{
    if(this->currentResult != NULL){
        QMenu *menu = new QMenu(this);
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->addAction("Export to CSV", this, SLOT(exportCurrentResultToCsv()));
        menu->addAction("Export to TXT", this, SLOT(exportCurrentResultToTxt()));
        menu->addAction("Export to PNG", this, SLOT(saveCurrentResultToPng()));
        menu->popup(ui->plot_cut->mapToGlobal(pos));
    }
}


void CsSerieWidget::updateCsList(){
    if(!this->ui->listWidget->updatesEnabled()){
        return;
    }
    this->ui->listWidget->setUpdatesEnabled(false);
    this->ui->listWidget->clear();

    QDir dir(this->workingDir);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files|QDir::NoDot|QDir::Readable, QDir::Name);


    for(QFileInfoList::const_iterator iterator = fileList.cbegin(); iterator != fileList.cend(); ++iterator){
        if (QFileInfo(iterator->filePath()).isFile() && QFileInfo(iterator->filePath()).suffix() == "txt" && iterator->fileName().startsWith(QString::fromStdString(this->file_prefix))){
            QListWidgetItem* item = new QListWidgetItem();
            item->setText(iterator->fileName());

            this->ui->listWidget->addItem(item);
        }
    }

    this->ui->listWidget->setUpdatesEnabled(true);
}

void CsSerieWidget::listItemSelected(QListWidgetItem* item, QListWidgetItem* prevItem){
    if(item == NULL){
        return;
    }

    if(this->currentResult != NULL){
        delete this->currentResult;
        this->currentResult = NULL;
    }

    // TODO fix memory leak of tests
    std::vector<TrajectoryTest>* tests = this->table->getTests();
    CalculatedCut* cut = new CalculatedCut(this->workingDir.toStdString() + "/" + item->text().toStdString(), tests);
    this->colorMap->updateColors(tests);

    this->initForCut(cut);
    this->draw(cut);

    this->currentResult = cut;

}


void CsSerieWidget::calculateButtonPressed(QWidget* button){
    if(button == ui->button_calculate){
        this->calculate(I_U2, false);
    }else if(button == ui->button_calculate_parallel){
        this->calculate(I_U2, true);
    }
}

std::string CsSerieWidget::generateFileName(int cs_num){
    std::string number;
    if(cs_num == 0){
        number = "0000";
    }else{
        number = std::string(std::max(3-(int)log10(cs_num), 0), '0').append(std::to_string(cs_num));
    }

    return this->file_prefix + number + ".txt";

}

void CsSerieWidget::calculateCsSerie(CrossSectionType type, double xMin, double xMax, double xStep,double yMin, double yMax, double yStep, double zMin, double zMax, double zPoints, std::vector<TrajectoryTest>* tests, std::string directory){
    double zStep = ((zMax-zMin)/(zPoints-1));
    double z;

    for(int l = 0; l < zPoints; ++l, z+=zStep){
        z = zMin + (l * zStep);
        this->progress = (double)l / zPoints;
        std::string filePath = directory + "/" + this->generateFileName(l);
        std::ifstream file(filePath);
        if(!file.good()){
            CalculatedCut* cut = this->calculator->calculateCrossSection(type, xMin, xMax, xStep, yMin, yMax, yStep, z, tests);

            if(!this->calculator->cancelled){
                cut->writeToTxt(filePath, "\t");
            }

            delete cut;
        }
    }
}

void CsSerieWidget::calculateParallelCsSerie(CrossSectionType type, double xMin, double xMax, double xPoints,double yMin, double yMax, double yPoints, double zMin, double zMax, double zPoints, std::vector<TrajectoryTest>* tests, std::string directory){
    double zStep = ((zMax-zMin)/(zPoints-1));
    double z;
    for(int l = 0; l < zPoints; ++l){
        z = zMin + (l * zStep);
        this->progress = (double)l / zPoints;
        std::string filePath = directory + "/" + this->generateFileName(l);
        std::ifstream file(filePath);
        if(!file.good()){
            CalculatedCut* cut = this->calculator->parallelCalculateCrossSection(type, xMin, xMax, xPoints, yMin, yMax, yPoints, z, tests);

            if(!this->calculator->cancelled){
                cut->writeToTxt(filePath, "\t");
            }

            delete cut;
        }
    }
}

void CsSerieWidget::calculate(CrossSectionType type, bool parallel){
    double xMin, xMax, xStep, yMin, yMax, yStep, zMin, zMax, zStep;

    xMin = this->ui->input_u2_from->value();
    xMax = this->ui->input_u2_to->value();
    xStep = this->ui->input_u2_step->value();
    yMin = this->ui->input_i_from->value();
    yMax = this->ui->input_i_to->value();
    yStep = this->ui->input_i_step->value();
    zMin = this->ui->input_u1_from->value();
    zMax = this->ui->input_u1_to->value();
    zStep = this->ui->input_u1_step->value();

    this->calculator = new TrajectoryCalculator(this->parameters);

    std::vector<TrajectoryTest>* tests = this->table->getTests();
    this->colorMap->updateColors(tests);
    QFuture<void> future;


    if(parallel){
        future = QtConcurrent::run(std::bind(&CsSerieWidget::calculateParallelCsSerie, this, type, xMin, xMax, xStep, yMin, yMax, yStep, zMin, zMax, zStep, tests, this->workingDir.toStdString()));
    }else{
        future = QtConcurrent::run(std::bind(&CsSerieWidget::calculateCsSerie, this, type, xMin, xMax, xStep, yMin, yMax, yStep, zMin, zMax, zStep, tests, this->workingDir.toStdString()));
    }

    this->FutureWatcher.setFuture(future);

    this->clock.start();
    this->progress = 0;
    this->lastProgress = 0;
    this->updateProgressTimer.start(100);

    this->ui->button_calculate->setDisabled(true);
    this->ui->button_calculate_parallel->setDisabled(true);

    this->ui->button_stop->setEnabled(true);
    this->ui->time->setEnabled(true);
    this->ui->progressBar->setEnabled(true);

}

void CsSerieWidget::cancelCalculation(){
    //this->ui->progressBar->setValue(0);
    this->ui->progressBar->setDisabled(true);

    this->ui->button_stop->setDisabled(true);
    this->ui->button_calculate->setEnabled(true);
    this->ui->button_calculate_parallel->setEnabled(true);

    this->ui->time->setDisabled(true);
    this->ui->time->setText("0:00");


    this->calculator->cancelled = true;
    this->updateProgressTimer.stop();

}

void CsSerieWidget::csCalculationFinished(){
    this->ui->button_stop->setDisabled(true);
    this->ui->button_calculate->setEnabled(true);
    this->ui->button_calculate_parallel->setEnabled(true);

    this->ui->time->setDisabled(true);
    this->ui->time->setText("0:00");

    this->ui->progressBar->setDisabled(true);
    this->updateProgressTimer.stop();
}

QString CsSerieWidget::formatTime(int timeInMs){
    int elapsedMins = timeInMs/1000/60;
    int elapsedSeconds = timeInMs/1000 - std::floor(timeInMs/1000/60)*60;
    return QString("%1:%2").arg(elapsedMins).arg(elapsedSeconds,2, 10, QChar('0'));
}

void CsSerieWidget::updateProgress()
{
    if(this->calculator->cancelled){
        return;
    }

    int elapsed = this->clock.elapsed();
    QString formattedTime = this->formatTime(elapsed);
    this->ui->time->setText(formattedTime);

    if(this->lastProgress < this->progress){
        int progress = std::round(this->progress * 100);
        this->ui->progressBar->setValue(progress);
        this->updateCsList();
        this->lastProgress = this->progress;
    }
}

