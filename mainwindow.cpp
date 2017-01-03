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
    this->ui->crosssection->updateParameters(this->parameters);

    this->connect(this->ui->actionLoad_parameters, &QAction::triggered, this, &MainWindow::loadParametersAction);
    this->connect(this->ui->actionSave_parameters, &QAction::triggered, this, &MainWindow::saveParametersAction);
    this->connect(this->ui->actionExport_to_TXT, &QAction::triggered, this, &MainWindow::exportTXTAction);
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

    this->ui->crosssection->updateParameters(this->parameters);
}

void MainWindow::loadParametersFromFile(std::string filename){
    double C1, C2, R, L, I;
    double Bp, B0, m0, m1, m2;
    double ro, tmax, h0, uhmax, ihmax;
    double n, u1_0, u2_0, i_0, t_test;
    double u1_from_u1i, u1_to_u1i, u1_step_u1i, u2_u1i, i_from_u1i, i_to_u1i, i_step_u1i;
    double i_from_u2i, u2_from_u2i, u2_to_u2i, u2_step_u2i, u1_u2i, i_to_u2i, i_step_u2i;
    double u1_from_u1u2, u1_to_u1u2, u1_step_u1u2, u2_from_u1u2, u2_to_u1u2, u2_step_u1u2, i_u1u2;

    std::ifstream file;
    file.open(filename);
    file >> std::setprecision(15) >> C1 >> C2 >> R >> L >> I >>
                                     Bp >> B0 >> m0 >> m1 >> m2 >> ro >>
                                     tmax >> h0 >> uhmax >> ihmax >> t_test >> n >>
                                     i_0 >> u1_0 >> u2_0 >>
                                     u1_from_u1i >> u1_to_u1i >> u1_step_u1i >> u2_u1i >> i_from_u1i >> i_to_u1i >> i_step_u1i >>
                                     i_from_u2i >> u2_from_u2i >> u2_to_u2i >> u2_step_u2i >> u1_u2i >> i_to_u2i >> i_step_u2i >>
                                     u1_from_u1u2 >> u1_to_u1u2 >> u1_step_u1u2 >> u2_from_u1u2 >> u2_to_u1u2 >> u2_step_u1u2 >> i_u1u2;


    file.close();

    this->parameters = new CircuitParameters(C1, C2, R, L, I, Bp, B0, m0, m1, m2, ro, tmax, h0, uhmax, ihmax, n, t_test);

    this->ui->trajectory->findChild<QDoubleSpinBox*>("input_u1_0")->setValue(u1_0);
    this->ui->trajectory->findChild<QDoubleSpinBox*>("input_u2_0")->setValue(u2_0);
    this->ui->trajectory->findChild<QDoubleSpinBox*>("input_i_0")->setValue(i_0);

    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_from_u1i")->setValue(u1_from_u1i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_to_u1i")->setValue(u1_to_u1i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_step_u1i")->setValue(u1_step_u1i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_u1i")->setValue(u2_u1i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_from_u1i")->setValue(i_from_u1i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_to_u1i")->setValue(i_to_u1i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_step_u1i")->setValue(i_step_u1i);

    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_from_u2i")->setValue(i_from_u2i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_from_u2i")->setValue(u2_from_u2i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_to_u2i")->setValue(u2_to_u2i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_step_u2i")->setValue(u2_step_u2i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_u2i")->setValue(u1_u2i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_to_u2i")->setValue(i_to_u2i);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_step_u2i")->setValue(i_step_u2i);

    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_from_u1u2")->setValue(u1_from_u1u2);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_to_u1u2")->setValue(u1_to_u1u2);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_step_u1u2")->setValue(u1_step_u1u2);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_from_u1u2")->setValue(u2_from_u1u2);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_to_u1u2")->setValue(u2_to_u1u2);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_step_u1u2")->setValue(u2_step_u1u2);
    this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_u1u2")->setValue(i_u1u2);


    this->ui->trajectory->updateParameters(this->parameters);
    this->ui->crosssection->updateParameters(this->parameters);


    std::string truncatedFileName;
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

    std::ofstream output;
    output.open(fileName.toStdString());


    output << std::fixed << std::setprecision(15) <<

              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_C1")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_C2")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_R")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_L")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_I")->value() << "\n" <<

              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_Bp")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_B0")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_m0")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_m1")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_m2")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_ro")->value() << "\n" <<

              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_tmax")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_h0")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_uhmax")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_ihmax")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_t_test")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_n")->value() << "\n" <<

              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_u1_0")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_u2_0")->value() << "\t" <<
              this->ui->trajectory->findChild<QDoubleSpinBox*>("input_i_0")->value() << "\n\n" <<

              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_from_u1i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_to_u1i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_step_u1i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_u1i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_from_u1i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_to_u1i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_step_u1i")->value() << "\n" <<

              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_from_u2i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_from_u2i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_to_u2i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_step_u2i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_u2i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_to_u2i")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_step_u2i")->value() << "\n" <<

              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_from_u1u2")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_to_u1u2")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u1_step_u1u2")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_from_u1u2")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_to_u1u2")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_u2_step_u1u2")->value() << "\t" <<
              this->ui->crosssection->findChild<QDoubleSpinBox*>("input_i_u1u2")->value() << "\n" <<

              "\n\nC1\tC2\tR\tL\tI\n" <<
              "Bp\tBo\tm0\tm1\tm2\n" <<
              "ro\ttmax\tho\tuhmax\tihmax\tt_test\tn\n" <<
              "i_zp\tu1_zp\tu2_zp\n\n" <<
              "u1_from_u1i\tu1_to_u1i\tu1_step_u1i\tu2_u1i\ti_from_u1i\ti_to_u1i\ti_step_u1i\n" <<
              "i_from_u2i\tu2_from_u2i\tu2_to_u2i\tu2_step_u2i\tu1_u2i\ti_to_u2i\ti_step_u2i\n" <<
              "u1_from_u1u2\tu1_to_u1u2\tu1_step_u1u2\tu2_from_u1u2\tu2_to_u1u2\tu2_step_u1u2\ti_u1u2";


    output.close();
}

void MainWindow::exportTXTAction(){
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save parameters file"), QString(), QString("Text file (*.txt);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    this->ui->trajectory->currentResult->writeToTXT(fileName.toStdString());
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
