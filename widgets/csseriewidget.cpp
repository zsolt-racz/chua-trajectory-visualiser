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

    this->connect(&this->updateProgressTimer, SIGNAL(timeout()), this, SLOT(updateProgress()));
    this->connect(this->ui->button_cancel_u1i, SIGNAL(clicked()), this, SLOT(cancelCalculation()));
    this->connect(this->ui->button_cancel_u2i, SIGNAL(clicked()), this, SLOT(cancelCalculation()));
    this->connect(this->ui->button_cancel_u1u2, SIGNAL(clicked()), this, SLOT(cancelCalculation()));

    this->connect(this->ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(listItemSelected(QListWidgetItem*, QListWidgetItem*)));

    this->connect(&this->FutureWatcher, SIGNAL (finished()), this, SLOT (csCalculationFinished()));
    this->connect(this->ui->plot_cut, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

    this->ui->resultTable->horizontalHeader()->hide();
    this->ui->resultTable->setEnabled(false);
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


void CsSerieWidget::activateUIFor(CrossSectionType type){
    if(type == CrossSectionType::I_U1){
        this->ui->input_u1_from_u1i->setEnabled(true);
        this->ui->input_u1_to_u1i->setEnabled(true);
        this->ui->input_u1_points_u1i->setEnabled(true);
        this->ui->input_i_from_u1i->setEnabled(true);
        this->ui->input_i_to_u1i->setEnabled(true);
        this->ui->input_i_points_u1i->setEnabled(true);
        this->ui->input_u2_from_u1i->setEnabled(true);
        this->ui->input_u2_to_u1i->setEnabled(true);
        this->ui->input_u2_cs_u1i->setEnabled(true);
        this->ui->button_calculate_u1i->setEnabled(true);
        this->ui->button_calculate_parallel_u1i->setEnabled(true);
        this->ui->tabWidget->setTabEnabled(1, true);
    }else if(type == CrossSectionType::I_U2){
        this->ui->input_u1_from_u2i->setEnabled(true);
        this->ui->input_u1_to_u2i->setEnabled(true);
        this->ui->input_u1_cs_u2i->setEnabled(true);
        this->ui->input_i_from_u2i->setEnabled(true);
        this->ui->input_i_to_u2i->setEnabled(true);
        this->ui->input_i_points_u2i->setEnabled(true);
        this->ui->input_u2_from_u2i->setEnabled(true);
        this->ui->input_u2_to_u2i->setEnabled(true);
        this->ui->input_u2_points_u2i->setEnabled(true);
        this->ui->button_calculate_u2i->setEnabled(true);
        this->ui->button_calculate_parallel_u2i->setEnabled(true);
        this->ui->tabWidget->setTabEnabled(0, true);
    }else if(type == CrossSectionType::U2_U1){
        this->ui->input_u1_from_u1u2->setEnabled(true);
        this->ui->input_u1_to_u1u2->setEnabled(true);
        this->ui->input_u1_points_u1u2->setEnabled(true);
        this->ui->input_i_from_u1u2->setEnabled(true);
        this->ui->input_i_to_u1u2->setEnabled(true);
        this->ui->input_i_cs_u1u2->setEnabled(true);
        this->ui->input_u2_from_u1u2->setEnabled(true);
        this->ui->input_u2_to_u1u2->setEnabled(true);
        this->ui->input_u2_points_u1u2->setEnabled(true);
        this->ui->button_calculate_u1u2->setEnabled(true);
        this->ui->button_calculate_parallel_u1u2->setEnabled(true);
        this->ui->tabWidget->setTabEnabled(2, true);
    }
}

void CsSerieWidget::disactivateUIFor(CrossSectionType type, bool enableButtons){
    if(type == CrossSectionType::I_U1){
        this->ui->input_u1_from_u1i->setEnabled(false);
        this->ui->input_u1_to_u1i->setEnabled(false);
        this->ui->input_u1_points_u1i->setEnabled(false);
        this->ui->input_i_from_u1i->setEnabled(false);
        this->ui->input_i_to_u1i->setEnabled(false);
        this->ui->input_i_points_u1i->setEnabled(false);
        this->ui->input_u2_from_u1i->setEnabled(false);
        this->ui->input_u2_to_u1i->setEnabled(false);
        this->ui->input_u2_cs_u1i->setEnabled(false);
        if(!enableButtons){
            this->ui->button_calculate_u1i->setEnabled(false);
            this->ui->button_calculate_parallel_u1i->setEnabled(false);
            this->ui->tabWidget->setTabEnabled(1, false);
        }else{
            this->ui->button_calculate_u1i->setEnabled(true);
            this->ui->button_calculate_parallel_u1i->setEnabled(true);
            this->ui->tabWidget->setTabEnabled(1, true);
        }
    }else if(type == CrossSectionType::I_U2){
        this->ui->input_u1_from_u2i->setEnabled(false);
        this->ui->input_u1_to_u2i->setEnabled(false);
        this->ui->input_u1_cs_u2i->setEnabled(false);
        this->ui->input_i_from_u2i->setEnabled(false);
        this->ui->input_i_to_u2i->setEnabled(false);
        this->ui->input_i_points_u2i->setEnabled(false);
        this->ui->input_u2_from_u2i->setEnabled(false);
        this->ui->input_u2_to_u2i->setEnabled(false);
        this->ui->input_u2_points_u2i->setEnabled(false);
        if(!enableButtons){
            this->ui->button_calculate_u2i->setEnabled(false);
            this->ui->button_calculate_parallel_u2i->setEnabled(false);
            this->ui->tabWidget->setTabEnabled(0, false);
        }else{
            this->ui->button_calculate_u2i->setEnabled(true);
            this->ui->button_calculate_parallel_u2i->setEnabled(true);
            this->ui->tabWidget->setTabEnabled(0, true);
        }
    }else if(type == CrossSectionType::U2_U1){
        this->ui->input_u1_from_u1u2->setEnabled(false);
        this->ui->input_u1_to_u1u2->setEnabled(false);
        this->ui->input_u1_points_u1u2->setEnabled(false);
        this->ui->input_i_from_u1u2->setEnabled(false);
        this->ui->input_i_to_u1u2->setEnabled(false);
        this->ui->input_i_cs_u1u2->setEnabled(false);
        this->ui->input_u2_from_u1u2->setEnabled(false);
        this->ui->input_u2_to_u1u2->setEnabled(false);
        this->ui->input_u2_points_u1u2->setEnabled(false);
        if(!enableButtons){
            this->ui->button_calculate_u1u2->setEnabled(false);
            this->ui->button_calculate_parallel_u1u2->setEnabled(false);
            this->ui->tabWidget->setTabEnabled(2, false);
        }else{
            this->ui->button_calculate_u1u2->setEnabled(true);
            this->ui->button_calculate_parallel_u1u2->setEnabled(true);
            this->ui->tabWidget->setTabEnabled(2, true);
        }
    }
}

void CsSerieWidget::selectWorkingDirAction(){
    QString dirName = QFileDialog::getExistingDirectory(this, QString("Select directory"), QString());

    if(dirName.isEmpty()){
        return;
    }

    this->workingDir = dirName;
    this->ui->folder_label->setText(dirName);

    if(!this->infoFileExists()){
        this->ui->tab_u2i->setEnabled(true);
        this->ui->tab_u1i->setEnabled(true);
        this->ui->tab_u1u2->setEnabled(true);
        this->activateUIFor(CrossSectionType::I_U1);
        this->activateUIFor(CrossSectionType::I_U2);
        this->activateUIFor(CrossSectionType::U2_U1);
    }else{
        this->updateUIByInfoFile(this->parseInfoFile());
    }

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

void CsSerieWidget::initForCut(CalculatedCrossSection* cut){
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

   /* QCPItemText *textLabel = new QCPItemText(customPlot);
    customPlot->addItem(textLabel);
    textLabel->setClipToAxisRect(false);
    textLabel->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0.5);
    textLabel->setText("u2 = 0");
    textLabel->setFont(QFont(font().family(), 12));*/


}

void CsSerieWidget::draw(CalculatedCrossSection* cut){
    QCustomPlot* customPlot = this->ui->plot_cut;

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = cut->cbegin(); vector_iterator != cut->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            this->colorMap->data()->setData(result_iterator->column, result_iterator->row, cut->getTestIndex(result_iterator->test));
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
    QString fileName = QFileDialog::getSaveFileName(this, QString("Export to TXT"), QString(), QString("Text files (*.txt)"));

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
    InfoFile infoFile = this->parseInfoFile();
    CalculatedCrossSection* cut;
    if(infoFile.type == I_U1){
        cut = new CalculatedCrossSection(infoFile.type, infoFile.yMin, infoFile.yMax, infoFile.ySize, infoFile.zMin, infoFile.zMax, infoFile.zSize, tests, this->workingDir.toStdString() + "/" + item->text().toStdString());
    }else if(infoFile.type == I_U2){
        cut = new CalculatedCrossSection(infoFile.type, infoFile.xMin, infoFile.xMax, infoFile.xSize, infoFile.zMin, infoFile.zMax, infoFile.zSize, tests, this->workingDir.toStdString() + "/" + item->text().toStdString());
    }else if(infoFile.type == U2_U1){
        cut = new CalculatedCrossSection(infoFile.type, infoFile.yMin, infoFile.yMax, infoFile.ySize, infoFile.xMin, infoFile.xMax, infoFile.xSize, tests, this->workingDir.toStdString() + "/" + item->text().toStdString());
    }

    this->colorMap->updateColors(tests);

    this->initForCut(cut);
    this->draw(cut);
    this->updateResultTable(cut, 0);
    this->ui->resultTable->setEnabled(true);

    this->currentResult = cut;

}


void CsSerieWidget::calculateButtonPressed(QWidget* button){
    if(button == ui->button_calculate_u1i){
        this->calculate(I_U1, false);
    }else if(button == ui->button_calculate_parallel_u1i){
        this->calculate(I_U1, true);
    }else if(button == ui->button_calculate_u2i){
        this->calculate(I_U2, false);
    }else if(button == ui->button_calculate_parallel_u2i){
        this->calculate(I_U2, true);
    }else if(button == ui->button_calculate_u1u2){
        this->calculate(U2_U1, false);
    }else if(button == ui->button_calculate_parallel_u1u2){
        this->calculate(U2_U1, true);
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
            CalculatedCrossSection* cut = this->calculator->calculateCrossSection(type, xMin, xMax, xStep, yMin, yMax, yStep, z, tests);

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
            CalculatedCrossSection* cut = this->calculator->parallelCalculateCrossSection(type, xMin, xMax, xPoints, yMin, yMax, yPoints, z, tests);

            if(!this->calculator->cancelled){
                cut->writeToTxt(filePath, "\t");
            }

            delete cut;
        }
        file.close();
    }
}

InfoFile CsSerieWidget::parseInfoFile(){
    InfoFile result;

    std::string filePath = this->workingDir.toStdString() + "/info.txt";
    std::ifstream file(filePath);

    int typeInt;

    file >> typeInt;
    result.type = static_cast<CrossSectionType>(typeInt);

    file >> result.xMin;
    file >> result.xMax;
    file >> result.xSize;

    file >> result.yMin;
    file >> result.yMax;
    file >> result.ySize;

    file >> result.zMin;
    file >> result.zMax;
    file >> result.zSize;

    file.close();

    return result;
}

InfoFile CsSerieWidget::createInfoFileByUi(CrossSectionType type){
    InfoFile result;
    result.type = type;

    if(type == I_U1){
        result.xMin = this->ui->input_u2_from_u1i->value();
        result.xMax =this->ui->input_u2_to_u1i->value();
        result.xSize = this->ui->input_u2_cs_u1i->value();
        result.yMin = this->ui->input_u1_from_u1i->value();
        result.yMax = this->ui->input_u1_to_u1i->value();
        result.ySize = this->ui->input_u1_points_u1i->value();
        result.zMin = this->ui->input_i_from_u1i->value();
        result.zMax = this->ui->input_i_to_u1i->value();
        result.zSize = this->ui->input_i_points_u1i->value();
    }else if(type == I_U2){
        result.xMin = this->ui->input_u2_from_u2i->value();
        result.xMax =this->ui->input_u2_to_u2i->value();
        result.xSize = this->ui->input_u2_points_u2i->value();
        result.yMin = this->ui->input_u1_from_u2i->value();
        result.yMax = this->ui->input_u1_to_u2i->value();
        result.ySize = this->ui->input_u1_cs_u2i->value();
        result.zMin = this->ui->input_i_from_u2i->value();
        result.zMax = this->ui->input_i_to_u2i->value();
        result.zSize = this->ui->input_i_points_u2i->value();
    }else if(type == U2_U1){
        result.xMin = this->ui->input_u2_from_u1u2->value();
        result.xMax =this->ui->input_u2_to_u1u2->value();
        result.xSize = this->ui->input_u2_points_u1u2->value();
        result.yMin = this->ui->input_u1_from_u1u2->value();
        result.yMax = this->ui->input_u1_to_u1u2->value();
        result.ySize = this->ui->input_u1_points_u1u2->value();
        result.zMin = this->ui->input_i_from_u1u2->value();
        result.zMax = this->ui->input_i_to_u1u2->value();
        result.zSize = this->ui->input_i_cs_u1u2->value();
    }

    return result;
}

void CsSerieWidget::writeInfoFile(InfoFile infoFile){
    std::string filePath = this->workingDir.toStdString() + "/info.txt";
    std::ofstream infoOutput(filePath);

        infoOutput << infoFile.type << std::setprecision(15) << "\n" <<
        infoFile.xMin << "\t" <<
        infoFile.xMax << "\t" <<
        infoFile.xSize  << "\n" <<
        infoFile.yMin << "\t" <<
        infoFile.yMax << "\t" <<
        infoFile.ySize << "\n" <<
        infoFile.zMin << "\t" <<
        infoFile.zMax << "\t" <<
        infoFile.zSize;

    infoOutput.close();
}

void CsSerieWidget::updateUIByInfoFile(InfoFile infoFile){
    if(infoFile.type == I_U1){
        this->ui->input_u2_from_u1i->setValue(infoFile.xMin);
        this->ui->input_u2_to_u1i->setValue(infoFile.xMax);
        this->ui->input_u2_cs_u1i->setValue(infoFile.xSize);
        this->ui->input_u1_from_u1i->setValue(infoFile.yMin);
        this->ui->input_u1_to_u1i->setValue(infoFile.yMax);
        this->ui->input_u1_points_u1i->setValue(infoFile.xSize);
        this->ui->input_i_from_u1i->setValue(infoFile.zMin);
        this->ui->input_i_to_u1i->setValue(infoFile.zMax);
        this->ui->input_i_points_u1i->setValue(infoFile.zSize);

        this->disactivateUIFor(I_U1, true);
        this->disactivateUIFor(I_U2);
        this->disactivateUIFor(U2_U1);

        this->ui->tabWidget->setCurrentIndex(1);

    }else if(infoFile.type == I_U2){
        this->ui->input_u2_from_u2i->setValue(infoFile.xMin);
        this->ui->input_u2_to_u2i->setValue(infoFile.xMax);
        this->ui->input_u2_points_u2i->setValue(infoFile.xSize);
        this->ui->input_u1_from_u2i->setValue(infoFile.yMin);
        this->ui->input_u1_to_u2i->setValue(infoFile.yMax);
        this->ui->input_u1_cs_u2i->setValue(infoFile.ySize);
        this->ui->input_i_from_u2i->setValue(infoFile.zMin);
        this->ui->input_i_to_u2i->setValue(infoFile.zMax);
        this->ui->input_i_points_u2i->setValue(infoFile.zSize);

        this->disactivateUIFor(I_U1);
        this->disactivateUIFor(I_U2, true);
        this->disactivateUIFor(U2_U1);

        this->ui->tabWidget->setCurrentIndex(0);
    }else if(infoFile.type == U2_U1){
        this->ui->input_u2_from_u1u2->setValue(infoFile.xMin);
        this->ui->input_u2_to_u1u2->setValue(infoFile.xMax);
        this->ui->input_u2_points_u1u2->setValue(infoFile.xSize);
        this->ui->input_u1_from_u1u2->setValue(infoFile.yMin);
        this->ui->input_u1_to_u1u2->setValue(infoFile.yMax);
        this->ui->input_u1_points_u1u2->setValue(infoFile.ySize);
        this->ui->input_i_from_u1u2->setValue(infoFile.zMin);
        this->ui->input_i_to_u1u2->setValue(infoFile.zMax);
        this->ui->input_i_cs_u1u2->setValue(infoFile.zSize);

        this->disactivateUIFor(I_U1);
        this->disactivateUIFor(I_U2);
        this->disactivateUIFor(U2_U1, true);

        this->ui->tabWidget->setCurrentIndex(2);
    }
}

bool CsSerieWidget::infoFileExists(){
    std::string filePath = this->workingDir.toStdString() + "/info.txt";

    std::ifstream file(filePath);
    bool result = file.good();
    file.close();

    return result;
}




void CsSerieWidget::calculate(CrossSectionType type, bool parallel){
    double xMin, xMax, xPoints, yMin, yMax, yPoints, zMin, zMax, zPoints;
    switch (type) {
    case I_U1:
        xMin = this->ui->input_u1_from_u1i->value();
        xMax = this->ui->input_u1_to_u1i->value();
        xPoints = this->ui->input_u1_points_u1i->value();
        yMin = this->ui->input_i_from_u1i->value();
        yMax = this->ui->input_i_to_u1i->value();
        yPoints = this->ui->input_i_points_u1i->value();
        zMin = this->ui->input_u2_from_u1i->value();
        zMax = this->ui->input_u2_to_u1i->value();
        zPoints = this->ui->input_u2_cs_u1i->value();

        this->ui->button_cancel_u1i->setEnabled(true);
        break;
    case I_U2:
        xMin = this->ui->input_u2_from_u2i->value();
        xMax = this->ui->input_u2_to_u2i->value();
        xPoints = this->ui->input_u2_points_u2i->value();
        yMin = this->ui->input_i_from_u2i->value();
        yMax = this->ui->input_i_to_u2i->value();
        yPoints = this->ui->input_i_points_u2i->value();
        zMin = this->ui->input_u1_from_u2i->value();
        zMax = this->ui->input_u1_to_u2i->value();
        zPoints = this->ui->input_u1_cs_u2i->value();

        this->ui->button_cancel_u2i->setEnabled(true);
        break;
    case U2_U1:
        xMin = this->ui->input_u1_from_u1u2->value();
        xMax = this->ui->input_u1_to_u1u2->value();
        xPoints = this->ui->input_u1_points_u1u2->value();
        yMin = this->ui->input_u2_from_u1u2->value();
        yMax = this->ui->input_u2_to_u1u2->value();
        yPoints = this->ui->input_u2_points_u1u2->value();
        zMin = this->ui->input_i_from_u1u2->value();
        zMax = this->ui->input_i_to_u1u2->value();
        zPoints = this->ui->input_i_cs_u1u2->value();

        this->ui->button_cancel_u1u2->setEnabled(true);
        break;
    }

    if(!this->infoFileExists()){
        InfoFile infoFile = this->createInfoFileByUi(type);
        this->writeInfoFile(infoFile);
        this->updateUIByInfoFile(infoFile);
    }

    this->ui->button_calculate_u1i->setDisabled(true);
    this->ui->button_calculate_parallel_u1i->setDisabled(true);
    this->ui->button_calculate_u2i->setDisabled(true);
    this->ui->button_calculate_parallel_u2i->setDisabled(true);
    this->ui->button_calculate_u1u2->setDisabled(true);
    this->ui->button_calculate_parallel_u1u2->setDisabled(true);

    this->calculator = new TrajectoryCalculator(this->parameters);

    std::vector<TrajectoryTest>* tests = this->table->getTests();
    this->colorMap->updateColors(tests);
    QFuture<void> future;


    if(parallel){
        future = QtConcurrent::run(std::bind(&CsSerieWidget::calculateParallelCsSerie, this, type, xMin, xMax, xPoints, yMin, yMax, yPoints, zMin, zMax, zPoints, tests, this->workingDir.toStdString()));
    }else{
        future = QtConcurrent::run(std::bind(&CsSerieWidget::calculateCsSerie, this, type, xMin, xMax, xPoints, yMin, yMax, yPoints, zMin, zMax, zPoints, tests, this->workingDir.toStdString()));
    }

    this->FutureWatcher.setFuture(future);

    this->clock.start();
    this->progress = 0;
    this->lastProgress = 0;
    this->updateProgressTimer.start(100);

    this->updateCsList();

    this->ui->time->setEnabled(true);
    this->ui->progressBar->setEnabled(true);

}

void CsSerieWidget::cancelCalculation(){
    this->ui->progressBar->setValue(0);
    this->ui->progressBar->setDisabled(true);

    this->ui->button_calculate_u1i->setEnabled(true);
    this->ui->button_calculate_parallel_u1i->setEnabled(true);
    this->ui->button_calculate_u2i->setEnabled(true);
    this->ui->button_calculate_parallel_u2i->setEnabled(true);
    this->ui->button_calculate_u1u2->setEnabled(true);
    this->ui->button_calculate_parallel_u1u2->setEnabled(true);

    this->ui->button_cancel_u1i->setDisabled(true);
    this->ui->button_cancel_u2i->setDisabled(true);
    this->ui->button_cancel_u1u2->setDisabled(true);

    this->ui->time->setDisabled(true);
    this->ui->time->setText("0:00");


    this->calculator->cancelled = true;
    this->updateProgressTimer.stop();

}

void CsSerieWidget::csCalculationFinished(){
    this->ui->button_calculate_u1i->setEnabled(true);
    this->ui->button_calculate_parallel_u1i->setEnabled(true);
    this->ui->button_calculate_u2i->setEnabled(true);
    this->ui->button_calculate_parallel_u2i->setEnabled(true);
    this->ui->button_calculate_u1u2->setEnabled(true);
    this->ui->button_calculate_parallel_u1u2->setEnabled(true);

    this->ui->button_cancel_u1i->setDisabled(true);
    this->ui->button_cancel_u2i->setDisabled(true);
    this->ui->button_cancel_u1u2->setDisabled(true);


    this->ui->time->setDisabled(true);
    this->ui->time->setText("0:00");

    this->updateCsList();
    this->ui->progressBar->setDisabled(true);
    this->ui->progressBar->setValue(0);
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

void CsSerieWidget::updateResultTable(CalculatedCrossSection* cut, int timeInMs){
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
    time->setText(this->formatTime(timeInMs));

    int allPoints = cut->columnCount * cut->rowCount;

    QTableWidgetItem *depth = new QTableWidgetItem;
    depth->setText(QString("%1").arg(cut->depth, 0, 'f'));

    float chaosPercent = ((float)chaosPoints / (float)allPoints) * 100;
    QTableWidgetItem *chaos = new QTableWidgetItem;
    chaos->setText(QString("%1% (%2)").arg(chaosPercent, 0, 'f', 2).arg(chaosPoints));

    float lcPercent = ((float)lcPoints / (float)allPoints) * 100;
    QTableWidgetItem *lc = new QTableWidgetItem;
    lc->setText(QString("%1% (%2)").arg(lcPercent, 0, 'f', 2).arg(lcPoints));

    float undPercent = ((float)undPoints / (float)allPoints) * 100;
    QTableWidgetItem *und = new QTableWidgetItem;
    und->setText(QString("%1% (%2)").arg(undPercent, 0, 'f', 2).arg(undPoints));

    this->ui->resultTable->setItem(0,0, depth);
    this->ui->resultTable->setItem(0,1, resolution);
    this->ui->resultTable->setItem(0,2, time);
    this->ui->resultTable->setItem(0,3, chaos);
    this->ui->resultTable->setItem(0,4, lc);
    this->ui->resultTable->setItem(0,5, und);
}
