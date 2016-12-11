#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->loadedFileLabel = new QLabel();
    this->ui->statusBar->addPermanentWidget(this->loadedFileLabel);

    this->loadParametersFromFile("parameters.txt");
    this->ui->trajectory->updateParameters(this->parameters);
    this->ui->cutwidget->updateParameters(this->parameters);

    this->connect(this->ui->actionLoad_parameters, &QAction::triggered, this, &MainWindow::loadParametersAction);
    this->connect(this->ui->actionSave_parameters, &QAction::triggered, this, &MainWindow::saveParametersAction);
    this->connect(this->ui->actionExport_to_CSV, &QAction::triggered, this, &MainWindow::exportCSVAction);
    this->connect(this->ui->actionExport_to_PLY, &QAction::triggered, this, &MainWindow::exportPLYAction);
    this->connect(this->ui->actionExit, &QAction::triggered, this, &MainWindow::exitAction);
    this->connect(this->ui->actionTrajectory, &QAction::triggered, this, &MainWindow::switchToTrajectoryAction);
    this->connect(this->ui->actionCrossSection, &QAction::triggered, this, &MainWindow::switchToCrossSectionAction);

    this->connect(this->ui->trajectory, SIGNAL(parametersChanged(CircuitParameters*)), this, SLOT(parametersChangedInTrajectory(CircuitParameters*)));
}



void MainWindow::parametersChangedInTrajectory(CircuitParameters* parameters){
    if(this->parameters != parameters){
        delete this->parameters;
        this->parameters = parameters;
    }

    this->ui->cutwidget->updateParameters(this->parameters);
}

void MainWindow::loadParametersFromFile(std::string filename){
    this->parameters = new CircuitParameters(filename);

    this->ui->trajectory->updateParameters(this->parameters);

    std::string truncatedFileName;
    this->ui->cutwidget->updateParameters(this->parameters);
    if(filename.length() > 60){
        truncatedFileName = "..." + filename.substr(filename.length() - 55, 55);
    }else{
        truncatedFileName = filename;
    }

    loadedFileLabel->setText(QString(("Loaded file: " +truncatedFileName).c_str()));
}



void MainWindow::loadParametersAction(){
    QString fileName = QFileDialog::getOpenFileName(this, QString("Open parameters file"), QString(), QString("Text files (*.txt);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->loadParametersFromFile(fileName.toStdString());
}

void MainWindow::saveParametersAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Text files (*.txt);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->parameters->saveToFile(fileName.toStdString());
}

void MainWindow::exportCSVAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Comma-separeted values (*.csv);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->ui->trajectory->currentResult->writeToCSV(fileName.toStdString());
}

void MainWindow::exportPLYAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Polygon File Format (*.ply);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->ui->trajectory->currentResult->writeToPLY(fileName.toStdString(), false);
}

void MainWindow::exitAction()
{
    close();
    qApp->quit();
}

void MainWindow::switchToTrajectoryAction(){
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::switchToCrossSectionAction(){
    this->ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
