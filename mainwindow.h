#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "Point3DT.h"
#include "circuitparameters.h"
#include <cmath>
#include <vector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void parametersChangedInTrajectory(CircuitParameters* parameters);

private:
    Ui::MainWindow* ui;
    CircuitParameters* parameters = NULL;

    void loadParametersFromFile(std::string filename);

    void exportCSVAction();
    void exportPLYAction();
    void exitAction();
    void switchToTrajectoryAction();
    void switchToCrossSectionAction();
    void loadParametersAction();
    void saveParametersAction();
};

#endif // MAINWINDOW_H
