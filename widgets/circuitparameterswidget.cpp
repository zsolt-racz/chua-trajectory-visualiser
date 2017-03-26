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
    this->ui->value_c1->setText(Utils::formatNumber(parameters->C1));
    this->ui->value_c2->setText(Utils::formatNumber(parameters->C2));
    this->ui->value_l->setText(Utils::formatNumber(parameters->L));
    this->ui->value_bp->setText(Utils::formatNumber(parameters->Bp));
    this->ui->value_b0->setText(Utils::formatNumber(parameters->B0));
    this->ui->value_r->setText(Utils::formatNumber(parameters->R));
    this->ui->value_ro->setText(Utils::formatNumber(parameters->ro));
    this->ui->value_i->setText(Utils::formatNumber(parameters->I));
    this->ui->value_m0->setText(Utils::formatNumber(parameters->m0));
    this->ui->value_m1->setText(Utils::formatNumber(parameters->m1));
    this->ui->value_m2->setText(Utils::formatNumber(parameters->m2));
    this->ui->value_tmax->setText(Utils::formatNumber(parameters->t_max));
    this->ui->value_h0->setText(Utils::formatNumber(parameters->h0));
    this->ui->value_ihmax->setText(Utils::formatNumber(parameters->iStepMax));
    this->ui->value_uhmax->setText(Utils::formatNumber(parameters->uStepMax));
    this->ui->value_n->setText(Utils::formatNumber(parameters->n));
    this->ui->value_t_test->setText(Utils::formatNumber(parameters->t_test));
}
