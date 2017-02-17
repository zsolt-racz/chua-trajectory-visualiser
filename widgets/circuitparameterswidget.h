#ifndef CIRCUITPARAMETERSWIDGET_H
#define CIRCUITPARAMETERSWIDGET_H

#include <QWidget>
#include "circuitparameters.h"

namespace Ui {
class CircuitParametersWidget;
}

class CircuitParametersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CircuitParametersWidget(QWidget *parent = 0);
    ~CircuitParametersWidget();
    void setParameters(CircuitParameters* parameters);

private:
    Ui::CircuitParametersWidget *ui;
};

#endif // CIRCUITPARAMETERSWIDGET_H
