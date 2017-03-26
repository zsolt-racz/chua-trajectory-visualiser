#ifndef CUSTOMDOUBLESPINBOX_H
#define CUSTOMDOUBLESPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QString>
#include <QLocale>
#include <QValidator>
#include <QRegExp>
#include <utils.h>
#include <iostream>

namespace Ui {
class CustomDoubleSpinBox;
}

class CustomDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT



public:
    explicit CustomDoubleSpinBox(QWidget *parent = 0);

    QString textFromValue(double value) const;
    double valueFromText(const QString &text) const;
    QValidator::State validate(QString &input, int &pos) const;
    ~CustomDoubleSpinBox();

};

#endif // CUSTOMDOUBLESPINBOX_H
