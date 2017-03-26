#ifndef CUSTOMSPINBOX_H
#define CUSTOMSPINBOX_H

#include <QWidget>
#include <QSpinBox>
#include <QValidator>
#include <QString>
#include <utils.h>

namespace Ui {
class CustomSpinBox;
}

class CustomSpinBox : public QSpinBox
{
    Q_OBJECT



public:
    explicit CustomSpinBox(QWidget *parent = 0);

    QString textFromValue(int value) const;
    int valueFromText(const QString &text) const;
    QValidator::State validate(QString &input, int &pos) const;
    ~CustomSpinBox();

};

#endif // CUSTOMSPINBOX_H
