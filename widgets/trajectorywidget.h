#ifndef TRAJECTORYWIDGET_H
#define TRAJECTORYWIDGET_H
#define NOMINMAX

#include <QWidget>
#include <QTime>
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
    void updateGuiByParameters();
    void updateParametersByGui();

private slots:
    void reCalculateAndReDraw();
    void stopAnimation();
    void reCalculateAndAnimate();
    void synchronizeRangeWithIU1();
    void synchronizeRangeWithIU2();
    void synchronizeRangeWithU1U2();

private:
    Ui::TrajectoryWidget *ui;
    CircuitParameters* parameters = NULL;
    void initPlots();
    void redrawPlots(Trajectory* result);
    void redrawPlot(QCustomPlot* plot, Trajectory* result, int xRange, int yRange );
    void resetPlots(QMouseEvent* event);
    void zoomPlot(QWheelEvent* event);
    void redrawResultTabe(Trajectory* result, int time);

    int reCalculate();
    void animatePlots();
    void animationStep();

};

#endif // TRAJECTORYWIDGET_H
