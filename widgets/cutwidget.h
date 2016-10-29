#ifndef CUT_H
#define CUT_H

#include <QList>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QGuiApplication>
#include <QtConcurrent/qtconcurrentmap.h>
#include <QWidget>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QProgressDialog>
#include <functional>
#include "qcustomplot/qcustomplot.h"
#include "TrajectoryCalculator.h"
#include "circuitparameters.h"
#include "trajectoryresulttype.h"

namespace Ui {
class CutWidget;
}

class CutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CutWidget(QWidget *parent = 0);
    ~CutWidget();

    void setParameters(CircuitParameters* parameters);
    void updateGuiByParameters();

private:
    Ui::CutWidget *ui;
    CircuitParameters* parameters = NULL;
    TrajectoryCalculator* calculator = NULL;
    QCPColorMap *colorMap = NULL;
    std::tuple<double, double, double> map(std::tuple<double, double, double> &parameters);

    void initPlot();
    void initForCut(CalculatedCut* cut);
    void reDraw(CalculatedCut* cut);
    void reDrawPartial(PartiallyCalculatedCut* cut);
    void updateResultTabe(CalculatedCut* cut, int timeInMs);
    QString formatTime(int timeInMs);
    QFutureWatcher<CalculatedCut*> FutureWatcher;
    QTimer updateProgressTimer;
    QTime clock;
    double lastProgress;

signals:
    void reCalculated(CalculatedCut* cut);

private slots:
    void reCalculateSerial();
    void reCalculateParallel();
    void reCalculate(bool parallel);
    void cancelCalculation();
    void calculationFinished();
    void updateProgressBar();
};

#endif // CUT_H
