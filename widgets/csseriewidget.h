#ifndef CSSERIEWIDGET_H
#define CSSERIEWIDGET_H

#include <cmath>
#include <string>
#include <QWidget>
#include <QFileDialog>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QSignalMapper>
#include <QTimer>
#include "TrajectoryCalculator.h"
#include "calculatedcut.h"
#include "circuitparameters.h"
#include "widgets/testinputwidget.h"
#include "crosssectiontype.h"
#include "crosssectionmap.h"

namespace Ui {
class CsSerieWidget;
}

class CsSerieWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CsSerieWidget(QWidget *parent = 0);
    ~CsSerieWidget();
    void updateParameters(CircuitParameters* parameters);
    void setTestTable(TestInputWidget* table);
    void calculate(CrossSectionType type, bool parallel);
    TrajectoryCalculator* calculator = NULL;
    void calculateCsSerie(CrossSectionType type, double xMin, double xMax, double xStep,double yMin, double yMax, double yStep, double zMin, double zMax, double zStep, std::vector<TrajectoryTest>* tests, std::string directory);
    void calculateParallelCsSerie(CrossSectionType type, double xMin, double xMax, double xStep,double yMin, double yMax, double yStep, double zMin, double zMax, double zStep, std::vector<TrajectoryTest>* tests, std::string directory);
    void updateCsList();
    void initPlot();
    void draw(CalculatedCut* cut);
    void initForCut(CalculatedCut* cut);
    void updateResultTable(CalculatedCut* cut, int timeInMs);

private:
    Ui::CsSerieWidget *ui;
    CircuitParameters* parameters = NULL;
    QString workingDir;
    TestInputWidget* table = NULL;
    QFutureWatcher<void> FutureWatcher;
    QTimer updateProgressTimer;
    QTime clock;
    QSignalMapper* calculatButtonSignalMapper;
    QString formatTime(int timeInMs);
    CrossSectionMap *colorMap = NULL;
    std::string generateFileName(int cs_num);
    CalculatedCut* currentResult = NULL;
    void writeInfoFile(CrossSectionType type);
    void activateUIFor(CrossSectionType type);
    void disactivateUIFor(CrossSectionType type, bool enableButtons = false);
    void updateUIByInfoFile();
    bool infoFileExists();

    double progress;
    double lastProgress;

    const std::string file_prefix = "cs_";

private slots:
    void calculateButtonPressed(QWidget* button);
    void selectWorkingDirAction();
    void csCalculationFinished();
    void cancelCalculation();
    void updateProgress();
    void listItemSelected(QListWidgetItem* item, QListWidgetItem* prevItem);
    void contextMenuRequest(QPoint pos);
    void saveCurrentResultToPng();
    void exportCurrentResultToTxt();
    void exportCurrentResultToCsv();
};

#endif // CSSERIEWIDGET_H
