#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H
#define NOMINMAX

#include "ui_trajectorywidget.h"
#include <QWidget>
#include <QTime>
#include "TrajectoryCalculator.h"
#include "circuitparameters.h"
#include "qcustomplot/qcustomplot.h"
#include "testinputwidget.h"
#include "qplot3d/QPlot3D.h"
#include "trajectory3dwindow.h"

namespace Ui {
class TrajectoryWidget;
}

class TrajectoryWidget : public QWidget
{
    Q_OBJECT

signals:
    void parametersChanged(CircuitParameters* parameters);

public:
    explicit TrajectoryWidget(QWidget *parent = 0);
    ~TrajectoryWidget();


    Trajectory* currentResult = NULL;
    QTimer* animationTimer;
    qint64 animationStart = 0;
    std::vector<Point3DT>::const_iterator nextAnimationPoint;
    void setTestTable(TestInputWidget* table);

    void updateParameters(CircuitParameters* parameters);

private slots:
    void reCalculateAndReDraw();
    void stopAnimation();
    void reCalculateAndAnimate();
    void synchronizeRangeWithIU1();
    void synchronizeRangeWithIU2();
    void synchronizeRangeWithU1U2();
    void updateParametersByGui();
    void contextMenuRequestIU1(QPoint pos);
    void contextMenuRequestIU2(QPoint pos);
    void contextMenuRequestU1U2(QPoint pos);
    void exportCurrentResultToTxt();
    void exportCurrentResultToCsv();
    void exportCurrentResultToPly();
    void savePlotIU1ToPng();
    void savePlotIU2ToPng();
    void savePlotU1U2ToPng();
    void show3DProjection();

private:
    Ui::TrajectoryWidget *ui;
    CircuitParameters* parameters = NULL;
    TestInputWidget* table = NULL;
    Trajectory3DWindow* window3d = NULL;
    bool updatingParameters = false;
    void initPlots();
    void redrawPlots(Trajectory* result);
    void redrawPlot(QCustomPlot* plot, Trajectory* result);
    void resetPlots(QMouseEvent* event);
    void resetPlotRanges();
    void zoomPlot(QWheelEvent* event);
    void redrawResultTabe(Trajectory* result, int time);

    int reCalculate();
    void animatePlots();
    void animationStep();

};

#endif // TRAJECTORYWIDGET_H
