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
    ChuaResult* currentResult = NULL;
    QTimer* animationTimer;
    qint64 animationStart = 0;
    std::vector<Point3DT*>::const_iterator nextAnimationPoint;

    void initPlots();
    void redrawPlots(ChuaResult* result);
    void redrawPlot(QCustomPlot* plot, ChuaResult* result, int xRange, int yRange );
    void resetPlots(QMouseEvent* event);
    void zoomPlot(QWheelEvent* event);
    void movePlot1(QMouseEvent* event);
    void movePlot2(QMouseEvent* event);
    void movePlot3(QMouseEvent* event);
    void redrawResultTabe(ChuaResult* result);
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
