#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ChuaCalculator.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "qcustomplot/qcustomplot.h"
#include "Point3DT.h"
#include <cmath>
#include <vector>
#include <iomanip>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow* ui;
    ChuaCalculator* calculator = NULL;
    std::vector<Point3DT*>* currentResult = NULL;
    QTimer* animationTimer;
    qint64 animationStart = 0;
    std::vector<Point3DT*>::iterator nextAnimationPoint;

    void initPlots();
    int getMaxMin(std::vector<Point3DT*>* result);
    Point3DT getMaxMins(std::vector<Point3DT*>* result);
    void redrawPlots(std::vector<Point3DT*>* result);
    void redrawPlot(QCustomPlot* plot, std::vector<Point3DT*>* result, int xRange, int yRange );
    ChuaCalculator* createCalculatorFromFile(std::string filename);
    ChuaCalculator* createCalculatorFromGui();
    void loadParametersFromFile(std::string filename);
    void reCalculate();
    void animatePlots();
    void animationStep();
    void stopAnimation();
    void reCalculateAndReDraw();
    void reCalculateAndAnimate();
    void updateGuiByCalculator(ChuaCalculator* calculator);
    void loadParametersAction();
    void saveParametersAction();
    void exportCSVAction();
    void exportPLYAction();
    void exitAction();
};

#endif // MAINWINDOW_H
