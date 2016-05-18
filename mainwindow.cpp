#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->loadParametersFromFile("parameters.txt");

    this->connect(this->ui->button_calculate, &QPushButton::clicked, this, &MainWindow::calculateAndDraw);
    this->connect(this->ui->actionLoad_parameters, &QAction::triggered, this, &MainWindow::loadParametersAction);
    this->connect(this->ui->actionSave_parameters, &QAction::triggered, this, &MainWindow::saveParametersAction);
    this->connect(this->ui->actionExport_to_CSV, &QAction::triggered, this, &MainWindow::exportCSVAction);
    this->connect(this->ui->actionExport_to_PLY, &QAction::triggered, this, &MainWindow::exportPLYAction);
    this->connect(this->ui->actionExit, &QAction::triggered, this, &MainWindow::exitAction);

    //TODO remove
    this->ui->input_i_0->setValue(0.000001);

    this->initPlots();
    this->calculateAndDraw();
}

void MainWindow::initPlots(){
    QCustomPlot* iu1Plot = ui->plot_iu1;
    QCPColorMap *iu1Map = new QCPColorMap(iu1Plot->xAxis, iu1Plot->yAxis);
    iu1Map->setInterpolate(true);
    iu1Map->data()->setSize(400,400);
    iu1Plot->setInteraction(QCP::iRangeDrag, true);
    iu1Plot->setInteraction(QCP::iRangeZoom, true);
    iu1Plot->addPlottable(iu1Map);
    iu1Plot->xAxis->setLabel("u1");
    iu1Plot->yAxis->setLabel("i");

    QCustomPlot* iu2Plot = ui->plot_iu2;
    QCPColorMap *iu2Map = new QCPColorMap(iu2Plot->xAxis, iu2Plot->yAxis);
    iu2Map->setInterpolate(true);
    iu2Map->data()->setSize(400,400);
    iu2Plot->setInteraction(QCP::iRangeDrag, true);
    iu2Plot->setInteraction(QCP::iRangeZoom, true);
    iu2Plot->addPlottable(iu2Map);
    iu2Plot->xAxis->setLabel("u2");
    iu2Plot->yAxis->setLabel("i");

    QCustomPlot* u1u2Plot = ui->plot_u1u2;
    QCPColorMap *u1u2Map = new QCPColorMap(u1u2Plot->xAxis, u1u2Plot->yAxis);
    u1u2Map->setInterpolate(true);
    u1u2Map->data()->setSize(400,400);
    u1u2Plot->setInteraction(QCP::iRangeDrag, true);
    u1u2Plot->setInteraction(QCP::iRangeZoom, true);
    u1u2Plot->addPlottable(u1u2Map);
    u1u2Plot->xAxis->setLabel("u1");
    u1u2Plot->yAxis->setLabel("u2");
}

int MainWindow::getMaxMin(std::vector<Point3DT*>* result){
    double maxMin = 0;
    for (std::vector<Point3DT*>::iterator point = result->begin(); point != result->end(); ++point) {
        if(maxMin < std::abs((*point)->i)){
            maxMin = std::abs((*point)->i);
        }
        if(maxMin < std::abs((*point)->u1)){
            maxMin = std::abs((*point)->u1);
        }
        if(maxMin < std::abs((*point)->u2)){
            maxMin = std::abs((*point)->u2);
        }
    }
    return (int) std::ceil(maxMin);
}

Point3DT MainWindow::getMaxMins(std::vector<Point3DT*>* result){
    int iMaxMin = 0;
    int u1MaxMin = 0;
    int u2MaxMin = 0;
    int tMaxMin = 0;

    for (std::vector<Point3DT*>::iterator point = result->begin(); point != result->end(); ++point) {
        if(iMaxMin < std::abs((*point)->i)){
            iMaxMin = std::abs((*point)->i);
        }
        if(u1MaxMin < std::abs((*point)->u1)){
            u1MaxMin = std::abs((*point)->u1);
        }
        if(u2MaxMin < std::abs((*point)->u2)){
            u2MaxMin = std::abs((*point)->u2);
        }
        if(tMaxMin < std::abs((*point)->t)){
            tMaxMin = std::abs((*point)->t);
        }
    }
    return Point3DT(iMaxMin, u1MaxMin, u2MaxMin, tMaxMin);
}

void MainWindow::redrawPlot(QCustomPlot* plot, std::vector<Point3DT*>* result, int xRange, int yRange ){
     QCPColorMap* colorMap = dynamic_cast<QCPColorMap*>(plot->plottable(0));

     colorMap->data()->fill(1);
     colorMap->data()->setRange(QCPRange(-xRange, xRange), QCPRange(-yRange, yRange));

     if(plot == this->ui->plot_iu1){
         for (std::vector<Point3DT*>::iterator point = result->begin(); point != result->end(); ++point) {
             colorMap->data()->setData((*point)->u1, (*point)->i, 0);
         }
     }else if(plot == this->ui->plot_iu2){
         for (std::vector<Point3DT*>::iterator point = result->begin(); point != result->end(); ++point) {
             colorMap->data()->setData((*point)->u2, (*point)->i, 0);
         }
     }else if(plot == this->ui->plot_u1u2){
         for (std::vector<Point3DT*>::iterator point = result->begin(); point != result->end(); ++point) {
             colorMap->data()->setData((*point)->u1, (*point)->u2, 0);
         }
     }

     colorMap->rescaleDataRange(true);

     plot->xAxis->setRange(-xRange,xRange);
     plot->yAxis->setRange(-yRange,yRange);
     plot->replot();
}

void MainWindow::redrawPlots(std::vector<Point3DT*>* result){
    Point3DT maxMins = this->getMaxMins(result);

    int iMaxMin = std::ceil(maxMins.i) + 1;
    int uMaxMin = std::max(std::ceil(maxMins.u1), std::ceil(maxMins.u2)) +1 ;

    this->redrawPlot(this->ui->plot_iu1, result, uMaxMin, iMaxMin);
    this->redrawPlot(this->ui->plot_iu2, result, uMaxMin, iMaxMin);
    this->redrawPlot(this->ui->plot_u1u2, result, uMaxMin, uMaxMin);
}

ChuaCalculator* MainWindow::createCalculatorFromFile(std::string filename){
    double C1,C2,L,Bp,B0,R,ro,I,m0,m1,m2,t_max,h;

    std::ifstream file;
    file.open(filename.c_str());
    file >> C1 >> C2 >> L >> Bp >> B0 >> R >> ro >> I >> m0 >> m1 >> m2 >> t_max >> h;
    file.close();

    return new ChuaCalculator(C1,C2,L,Bp,B0,R,ro,I,m0,m1,m2,t_max,h);
}

ChuaCalculator* MainWindow::createCalculatorFromGui(){
    return new ChuaCalculator(this->ui->input_C1->value(),
                              this->ui->input_C2->value(),
                              this->ui->input_L->value(),
                              this->ui->input_Bp->value(),
                              this->ui->input_B0->value(),
                              this->ui->input_R->value(),
                              this->ui->input_ro->value(),
                              this->ui->input_I->value(),
                              this->ui->input_m0->value(),
                              this->ui->input_m1->value(),
                              this->ui->input_m2->value(),
                              this->ui->input_tmax->value(),
                              this->ui->input_h->value()
                              );
}

void MainWindow::loadParametersFromFile(std::string filename){
    this->calculator = this->createCalculatorFromFile(filename);
    this->updateGuiByCalculator(calculator);
}

void MainWindow::updateGuiByCalculator(ChuaCalculator* calculator){
    this->ui->input_C1->setValue(calculator->C1);
    this->ui->input_C2->setValue(calculator->C2);
    this->ui->input_L->setValue(calculator->L);
    this->ui->input_Bp->setValue(calculator->Bp);
    this->ui->input_B0->setValue(calculator->B0);
    this->ui->input_R->setValue(calculator->R);
    this->ui->input_ro->setValue(calculator->ro);
    this->ui->input_I->setValue(calculator->I);
    this->ui->input_m0->setValue(calculator->m0);
    this->ui->input_m1->setValue(calculator->m1);
    this->ui->input_m2->setValue(calculator->m2);
    this->ui->input_tmax->setValue(calculator->t_max);
    this->ui->input_h->setValue(calculator->h);
}

void MainWindow::loadParametersAction(){
    QString fileName = QFileDialog::getOpenFileName(this, QString("Open parameters file"), QString(), QString("Text files (*.txt);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->loadParametersFromFile(fileName.toStdString());
    this->calculateAndDraw();
}

void MainWindow::saveParametersAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Text files (*.txt);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    std::ofstream output;
    output.open(fileName.toStdString().c_str());

    output << std::fixed << std::setprecision(11) <<
             this->ui->input_C1->value() << "\t" <<
            this->ui->input_C2->value() << "\t" <<
            this->ui->input_L->value() << "\t" <<
            this->ui->input_Bp->value() << "\t" <<
            this->ui->input_B0->value() << "\t" <<
            this->ui->input_R->value() << "\t" <<
            this->ui->input_ro->value() << "\t" <<
            this->ui->input_I->value() << "\t" <<
            this->ui->input_m0->value() << "\t" <<
            this->ui->input_m1->value() << "\t" <<
            this->ui->input_m2->value() << "\t" <<
            this->ui->input_tmax->value() << "\t" <<
            this->ui->input_h->value();

    output.close();
}

void MainWindow::exportCSVAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Comma-separeted values (*.csv);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->calculator->writeToCSV(fileName.toStdString(), this->currentResult);
}

void MainWindow::exportPLYAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Polygon File Format (*.ply);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->calculator->writeToPLY(fileName.toStdString(), this->currentResult, false);
}

void MainWindow::calculateAndDraw(){
    if(this->calculator != NULL){
        delete this->calculator;
        this->calculator = NULL;
    }
    if(this->currentResult != NULL){
        for (std::vector<Point3DT*>::iterator point = this->currentResult->begin(); point != this->currentResult->end(); ++point) {
            delete (*point);
        }
        delete this->currentResult;
        this->currentResult = NULL;
    }
    this->calculator = this->createCalculatorFromGui();

    this->currentResult = calculator->calculateTrajectory(this->ui->input_i_0->value(), this->ui->input_u1_0->value(), this->ui->input_u2_0->value());
    calculator->printParameters();

    this->redrawPlots(this->currentResult);
}


void MainWindow::exitAction()
{
    close();
    qApp->quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
