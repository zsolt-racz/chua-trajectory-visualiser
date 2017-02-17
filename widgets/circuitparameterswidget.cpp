#include "widgets/circuitparameterswidget.h"
#include "ui_circuitparameterswidget.h"

CircuitParametersWidget::CircuitParametersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircuitParametersWidget)
{
    ui->setupUi(this);
}

CircuitParametersWidget::~CircuitParametersWidget()
{
    delete ui;
}

void CircuitParametersWidget::setParameters(CircuitParameters* parameters){
    this->ui->value_c1->setText(QString::number(parameters->C1));
    this->ui->value_c2->setText(QString::number(parameters->C2));
    this->ui->value_l->setText(QString::number(parameters->L));
    this->ui->value_bp->setText(QString::number(parameters->Bp));
    this->ui->value_b0->setText(QString::number(parameters->B0));
    this->ui->value_r->setText(QString::number(parameters->R));
    this->ui->value_ro->setText(QString::number(parameters->ro));
    this->ui->value_i->setText(QString::number(parameters->I));
    this->ui->value_m0->setText(QString::number(parameters->m0));
    this->ui->value_m1->setText(QString::number(parameters->m1));
    this->ui->value_m2->setText(QString::number(parameters->m2));
    this->ui->value_tmax->setText(QString::number(parameters->t_max));
    this->ui->value_h0->setText(QString::number(parameters->h0));
    this->ui->value_ihmax->setText(QString::number(parameters->iStepMax));
    this->ui->value_uhmax->setText(QString::number(parameters->uStepMax));
    this->ui->value_n->setText(QString::number(parameters->n));
    this->ui->value_t_test->setText(QString::number(parameters->t_test));
}
