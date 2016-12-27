#ifndef TESTINPUTWIDGET_H
#define TESTINPUTWIDGET_H

#include <QWidget>
#include <QColor>
#include <QSpinBox>
#include <QComboBox>
#include <vector>
#include "trajectorytest.h"
#include "trajectoryresulttype.h"

namespace Ui {
class TestInputWidget;
}

class TestInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestInputWidget(QWidget *parent = 0);
    ~TestInputWidget();

    void addRow(QString name, QString type, QString color, double u1Lo, double u1Hi, double u2Lo, double u2Hi, double iLo, double iHi);
    std::vector<TrajectoryTest>* getTests();

private:
    Ui::TestInputWidget *ui;
    QDoubleSpinBox* createSpinBox(QWidget* parent);
    QDoubleSpinBox* createSpinBox(QWidget* parent, double value);
    QComboBox* createColorCombobox(QWidget* parent);
    QComboBox* createColorCombobox(QWidget* parent, QString value);
    QComboBox* createTypeCombobox(QWidget* parent);
    QComboBox* createTypeCombobox(QWidget* parent, QString value);

private slots:
    void addChaosRow();
    void addLCRow();
    void removeSelectedRows();
};

#endif // TESTINPUTWIDGET_H
