#include "testinputwidget.h"
#include "ui_testinputwidget.h"

TestInputWidget::TestInputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestInputWidget)
{
    ui->setupUi(this);

    this->connect(this->ui->add_cha, SIGNAL(clicked()), this, SLOT(addChaosRow()));
    this->connect(this->ui->add_lc, SIGNAL(clicked()), this, SLOT(addLCRow()));
    this->connect(this->ui->delete_selection, SIGNAL(clicked()), this, SLOT(removeSelectedRows()));

}

void TestInputWidget::addRow(QString name, QString type, bool wait, QString color, double u1Lo, double u1Hi, double u2Lo, double u2Hi, double iLo, double iHi){
    QTableWidget* table = this->ui->table;

    int row = table->rowCount();

    table->setRowCount(row+1);

    // Prepare centered widget for checkbox wait
    QWidget * wbw = new QWidget();
    QHBoxLayout *wbl = new QHBoxLayout();
    wbl->setAlignment( Qt::AlignCenter );
    wbl->addWidget(this->createTypeCheckbox(table, wait));
    wbw->setLayout(wbl);

    table->setItem(row, 0, new QTableWidgetItem(name));
    table->setCellWidget(row, 1, this->createTypeCombobox(table, type));
    table->setCellWidget(row, 2, wbw);
    table->setCellWidget(row, 3, this->createColorCombobox(table, color));
    table->setCellWidget(row, 4, this->createSpinBox(table, u1Lo));
    table->setCellWidget(row, 5, this->createSpinBox(table, u1Hi));
    table->setCellWidget(row, 6, this->createSpinBox(table, u2Lo));
    table->setCellWidget(row, 7, this->createSpinBox(table, u2Hi));
    table->setCellWidget(row, 8, this->createSpinBox(table, iLo));
    table->setCellWidget(row, 9, this->createSpinBox(table, iHi));

    table->setColumnWidth(2, 50);

    /*table->setColumnWidth(0, 75);
    table->setColumnWidth(1, 75);
    table->setColumnWidth(2, 75);*/
}

void TestInputWidget::addChaosRow(){
    this->addRow("", QString("Chaos"), true, "", 0, 0, 0, 0, 0, 0);
}

void TestInputWidget::addLCRow(){
    this->addRow("", QString("LC"), false, "", -9999, 9999, -9999, 9999, -9999, 9999);
}

void TestInputWidget::removeSelectedRows(){
    QTableWidget* table = this->ui->table;

    QModelIndexList selectedRows = table->selectionModel()->selectedRows();
    for(QModelIndexList::const_iterator row = selectedRows.cbegin(); row != selectedRows.cend(); ++row){
        table->removeRow(row->row());
    }
}

void TestInputWidget::clearRows(){
    QTableWidget* table = this->ui->table;
    table->setRowCount(0);
}

CustomDoubleSpinBox* TestInputWidget::createSpinBox(QWidget* parent){
    CustomDoubleSpinBox* result = new CustomDoubleSpinBox(parent);
    result->setDecimals(4);
    result->setMinimum(-9999);
    result->setMaximum(9999);

    return result;
}

CustomDoubleSpinBox* TestInputWidget::createSpinBox(QWidget* parent, double value){
    CustomDoubleSpinBox* result = this->createSpinBox(parent);
    result->setValue(value);

    return result;
}

QComboBox* TestInputWidget::createColorCombobox(QWidget* parent){
    QComboBox* result = new QComboBox(parent);

    result->addItem(QString("aqua"));
    result->addItem(QString("blue"));
    result->addItem(QString("brown"));
    result->addItem(QString("gray"));
    result->addItem(QString("green"));
    result->addItem(QString("lime"));
    result->addItem(QString("magenta"));
    result->addItem(QString("orange"));
    result->addItem(QString("purple"));
    result->addItem(QString("red"));
    result->addItem(QString("yellow"));

    return result;
}

QComboBox* TestInputWidget::createColorCombobox(QWidget* parent, QString value){
    QComboBox* result = this->createColorCombobox(parent);

    result->setCurrentText(value);

    return result;
}

QComboBox* TestInputWidget::createTypeCombobox(QWidget* parent){
    QComboBox* result = new QComboBox(parent);

    result->addItem(QString("Chaos"));
    result->addItem(QString("LC"));

    return result;
}

QComboBox* TestInputWidget::createTypeCombobox(QWidget* parent, QString value){
    QComboBox* result = this->createTypeCombobox(parent);

    result->setCurrentText(value);

    return result;
}

QCheckBox* TestInputWidget::createTypeCheckbox(QWidget* parent, bool checked){
    QCheckBox* result = new QCheckBox(parent);

    result->setChecked(checked);

    return result;
}

std::vector<TrajectoryTest>* TestInputWidget::getTests(){
   QTableWidget* table = this->ui->table;
   std::vector<TrajectoryTest>* result = new std::vector<TrajectoryTest>();

   for(int i = 0; i < table->rowCount(); i++){
       QComboBox* typeWidget = static_cast<QComboBox*>(table->cellWidget(i, 1));
       QCheckBox* waitWidget = static_cast<QCheckBox*>(table->cellWidget(i, 2)->layout()->itemAt(0)->widget());
       QComboBox* colorWidget = static_cast<QComboBox*>(table->cellWidget(i, 3));
       QDoubleSpinBox* u1LoWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 4));
       QDoubleSpinBox* u1HiWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 5));
       QDoubleSpinBox* u2LoWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 6));
       QDoubleSpinBox* u2HiWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 7));
       QDoubleSpinBox* iLoWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 8));
       QDoubleSpinBox* iHiWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 9));

       TrajectoryResultType type;
       if(typeWidget->currentText().toStdString() == "Chaos"){
           type = TrajectoryResultType::CHA;
       }else if(typeWidget->currentText().toStdString() == "LC"){
           type = TrajectoryResultType::LC;
       }
       bool checked = waitWidget->isChecked();
       result->push_back(TrajectoryTest(table->item(i,0)->text().toStdString(), type, checked, colorWidget->currentText().toStdString(), u1LoWidget->value(), u1HiWidget->value(), u2LoWidget->value(), u2HiWidget->value(), iLoWidget->value(), iHiWidget->value()));
   }

   return result;
}

TestInputWidget::~TestInputWidget()
{
    delete ui;
}
