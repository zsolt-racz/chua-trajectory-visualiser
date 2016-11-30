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
#include <QSignalMapper>
#include <QPoint>
#include <QFileDialog>
#include <functional>
#include "qcustomplot/qcustomplot.h"
#include "TrajectoryCalculator.h"
#include "circuitparameters.h"
#include "trajectoryresulttype.h"
#include "exprtk/exprtk.hpp"

namespace Ui {
class CutWidget;
}

class CutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CutWidget(QWidget *parent = 0);
    ~CutWidget();

    void updateParameters(CircuitParameters* parameters);

private:
    Ui::CutWidget *ui;
    CircuitParameters* parameters = NULL;
    TrajectoryCalculator* calculator = NULL;
    CalculatedCut* currentResult = NULL;
    QCPColorMap *colorMap = NULL;
    std::tuple<double, double, double> map(std::tuple<double, double, double> &parameters);

    void initPlot();
    void initForCut(CalculatedCut* cut);
    void reCalculate(CrossSectionType type, bool parallel);
    void reDraw(CalculatedCut* cut);
    void reDrawPartial(PartiallyCalculatedCut* cut);
    void updateResultTable(CalculatedCut* cut, int timeInMs);
    QString formatTime(int timeInMs);
    QFutureWatcher<CalculatedCut*> FutureWatcher;
    QTimer updateProgressTimer;
    QTime clock;
    QSignalMapper* calculatButtonSignalMapper;
    QSignalMapper* testChangedSignalMapper;
    double lastProgress;

signals:
    void reCalculated(CalculatedCut* cut);

private slots:
    void calculateButtonPressed(QWidget* button);
    void cancelCalculation();
    void calculationFinished();
    void updateProgressBar();
    void testExpressionChanged(QWidget* textEdit);
    void contextMenuRequest(QPoint pos);
    void saveCurrentResultToPng();
    void exportCurrentResultToCsv();
};

#endif // CUT_H
