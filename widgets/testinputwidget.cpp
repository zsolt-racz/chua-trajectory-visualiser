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

    //this->addRow("Atraktor 1", QString("Chaos"), QString("aqua"), -0.25, 0.25, -5.25, -4.75, -5, 5);
    //this->addRow("LC", QString("LC"), QString("gray"), -1000, 1000, -1000, 1000, -30, 30);

}

void TestInputWidget::addRow(QString name, QString type, QString color, double u1Lo, double u1Hi, double u2Lo, double u2Hi, double iLo, double iHi){
    QTableWidget* table = this->ui->table;

    int row = table->rowCount();

    table->setRowCount(row+1);

    table->setItem(row, 0, new QTableWidgetItem(name));
    table->setCellWidget(row, 1, this->createTypeCombobox(table, type));
    table->setCellWidget(row, 2, this->createColorCombobox(table, color));
    table->setCellWidget(row, 3, this->createSpinBox(table, u1Lo));
    table->setCellWidget(row, 4, this->createSpinBox(table, u1Hi));
    table->setCellWidget(row, 5, this->createSpinBox(table, u2Lo));
    table->setCellWidget(row, 6, this->createSpinBox(table, u2Hi));
    table->setCellWidget(row, 7, this->createSpinBox(table, iLo));
    table->setCellWidget(row, 8, this->createSpinBox(table, iHi));

    table->setColumnWidth(0, 75);
    table->setColumnWidth(1, 75);
    table->setColumnWidth(2, 75);
}

void TestInputWidget::addChaosRow(){
    this->addRow("", QString("Chaos"), "", 0, 0, 0, 0, 0, 0);
}

void TestInputWidget::addLCRow(){
    this->addRow("", QString("LC"), "", -1000, 1000, -1000, 1000, -1000, 1000);
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

QDoubleSpinBox* TestInputWidget::createSpinBox(QWidget* parent){
    QDoubleSpinBox* result = new QDoubleSpinBox(parent);
    result->setDecimals(4);
    result->setMinimum(-999);
    result->setMaximum(999);

    return result;
}

QDoubleSpinBox* TestInputWidget::createSpinBox(QWidget* parent, double value){
    QDoubleSpinBox* result = this->createSpinBox(parent);
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

std::vector<TrajectoryTest>* TestInputWidget::getTests(){
   QTableWidget* table = this->ui->table;
   std::vector<TrajectoryTest>* result = new std::vector<TrajectoryTest>();

   for(int i = 0; i < table->rowCount(); i++){
       QComboBox* typeWidget = static_cast<QComboBox*>(table->cellWidget(i, 1));
       QComboBox* colorWidget = static_cast<QComboBox*>(table->cellWidget(i, 2));
       QDoubleSpinBox* u1LoWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 3));
       QDoubleSpinBox* u1HiWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 4));
       QDoubleSpinBox* u2LoWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 5));
       QDoubleSpinBox* u2HiWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 6));
       QDoubleSpinBox* iLoWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 7));
       QDoubleSpinBox* iHiWidget = static_cast<QDoubleSpinBox*>(table->cellWidget(i, 8));

       TrajectoryResultType type;
       if(typeWidget->currentText().toStdString() == "Chaos"){
           type = TrajectoryResultType::CHA;
       }else if(typeWidget->currentText().toStdString() == "LC"){
           type = TrajectoryResultType::LC;
       }
       result->push_back(TrajectoryTest(table->item(i,0)->text().toStdString(), type, colorWidget->currentText().toStdString(), u1LoWidget->value(), u1HiWidget->value(), u2LoWidget->value(), u2HiWidget->value(), iLoWidget->value(), iHiWidget->value()));
   }

   return result;
}

TestInputWidget::~TestInputWidget()
{
    delete ui;
}
