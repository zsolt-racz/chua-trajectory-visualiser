#include "widgets/cutwidget.h"
#include "ui_cutwidget.h"

CutWidget::CutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CutWidget)
{
    ui->setupUi(this);
}

CutWidget::~CutWidget()
{
    delete ui;
}
