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
#include "trajectoryresult.h"
#include "trajectorytest.h"
#include "trajectoryresulttype.h"
#include "crosssectionmap.h"
#include <QStandardItemModel>

namespace Ui {
class CrossSectionWidget;
}

class CrossSectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CrossSectionWidget(QWidget *parent = 0);
    ~CrossSectionWidget();

    void updateParameters(CircuitParameters* parameters);

private:
    Ui::CrossSectionWidget *ui;
    CircuitParameters* parameters = NULL;
    TrajectoryCalculator* calculator = NULL;
    CalculatedCrossSection* currentResult = NULL;
    CrossSectionMap *colorMap = NULL;
    std::tuple<double, double, double> map(std::tuple<double, double, double> &parameters);

    void initPlot();
    void initForCut(CalculatedCrossSection* cut);
    void reCalculate(CrossSectionType type, bool parallel);
    void reDraw(CalculatedCrossSection* cut);
    void reDrawPartial(PartiallyCalculatedCrossSection* cut);
    void updateResultTable(CalculatedCrossSection* cut, int timeInMs);
    QString formatTime(int timeInMs);
    QFutureWatcher<CalculatedCrossSection*> FutureWatcher;
    QTimer updateProgressTimer;
    QTime clock;
    QSignalMapper* calculatButtonSignalMapper;
    QSignalMapper* testChangedSignalMapper;
    double lastProgress;

signals:
    void reCalculated(CalculatedCrossSection* cut);

private slots:
    void calculateButtonPressed(QWidget* button);
    void cancelCalculation();
    void calculationFinished();
    void updateProgressBar();
    void contextMenuRequest(QPoint pos);
    void saveCurrentResultToPng();
    void exportCurrentResultToTxt();
    void exportCurrentResultToCsv();
};

#endif // CUT_H
