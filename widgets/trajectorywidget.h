#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H

#include <QWidget>
#include "TrajectoryCalculator.h"
#include "circuitparameters.h"
#include "qcustomplot/qcustomplot.h"

namespace Ui {
class TrajectoryWidget;
}

class TrajectoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrajectoryWidget(QWidget *parent = 0);
    ~TrajectoryWidget();


    Trajectory* currentResult = NULL;
    QTimer* animationTimer;
    qint64 animationStart = 0;
    std::vector<Point3DT*>::const_iterator nextAnimationPoint;

    void setParameters(CircuitParameters* parameters);
    void updateParameters(CircuitParameters* parameters);
    void reCalculateAndReDraw();


private:
    Ui::TrajectoryWidget *ui;
    CircuitParameters* parameters = NULL;
    void initPlots();
    void redrawPlots(Trajectory* result);
    void redrawPlot(QCustomPlot* plot, Trajectory* result, int xRange, int yRange );
    void resetPlots(QMouseEvent* event);
    void zoomPlot(QWheelEvent* event);
    void movePlot1(QMouseEvent* event);
    void movePlot2(QMouseEvent* event);
    void movePlot3(QMouseEvent* event);
    void redrawResultTabe(Trajectory* result);

    void reCalculate();
    void animatePlots();
    void animationStep();
    void stopAnimation();
    void reCalculateAndAnimate();


    TrajectoryCalculator* createCalculatorFromGui();
};

#endif // TRAJECTORYWIDGET_H
