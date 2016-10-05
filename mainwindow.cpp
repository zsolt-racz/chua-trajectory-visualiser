#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->parameters = new CircuitParameters();
    this->ui->trajectory->setParameters(this->parameters);
    this->loadParametersFromFile("parameters.txt");

    this->connect(this->ui->actionLoad_parameters, &QAction::triggered, this, &MainWindow::loadParametersAction);
    this->connect(this->ui->actionSave_parameters, &QAction::triggered, this, &MainWindow::saveParametersAction);
    this->connect(this->ui->actionExport_to_CSV, &QAction::triggered, this, &MainWindow::exportCSVAction);
    this->connect(this->ui->actionExport_to_PLY, &QAction::triggered, this, &MainWindow::exportPLYAction);
    this->connect(this->ui->actionExit, &QAction::triggered, this, &MainWindow::exitAction);
    this->connect(this->ui->actionTrajectory, &QAction::triggered, this, &MainWindow::switchToTrajectoryAction);
    this->connect(this->ui->actionCut, &QAction::triggered, this, &MainWindow::switchToCutAction);
}



void MainWindow::loadParametersFromFile(std::string filename){
    this->parameters->loadFromFile(filename);

    this->ui->trajectory->updateParameters(this->parameters);
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

void MainWindow::switchToCutAction(){
    this->ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
