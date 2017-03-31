#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QLocale>

#include "ui_mainwindow.h"
#include "Point3DT.h"
#include "circuitparameters.h"
#include <cmath>
#include <vector>
#include <widgets/testinputwidget.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void parametersChangedInTrajectory(CircuitParameters* parameters);
    void aboutAction();

private:
    Ui::MainWindow* ui;
    CircuitParameters* parameters = NULL;
    QLabel* loadedFileLabel = NULL;

    std::string trim(const std::string& str, const std::string& whitespace);
    void loadParametersFromFile(std::string filename);

    void exitAction();
    void switchToTrajectoryAction();
    void switchToCrossSectionAction();
    void switchToCSSerieAction();
    void loadParametersAction();
    void saveParametersAction();
    void setStatusText(std::string filename);
};

#endif // MAINWINDOW_H
