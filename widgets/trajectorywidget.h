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

private:
    Ui::TrajectoryWidget *ui;
    CircuitParameters* parameters = NULL;
    TestInputWidget* table = NULL;
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
