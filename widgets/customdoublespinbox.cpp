#include "customdoublespinbox.h"

CustomDoubleSpinBox::CustomDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{

}

CustomDoubleSpinBox::~CustomDoubleSpinBox()
{

}

QString CustomDoubleSpinBox::textFromValue(double value) const
{
    return Utils::formatNumber(value);
}

double CustomDoubleSpinBox::valueFromText(const QString &text) const
{
    return Utils::parseDouble(text);
}

QValidator::State CustomDoubleSpinBox::validate(QString &input, int &pos) const
{
    QRegExp re("[+-]?[0-9 ]+((,|\.)[0-9 ]+)?");

    if(re.exactMatch(input)){
        return QValidator::State::Acceptable;
    }else{
        QRegExp re("[+-]?[0-9 ]*((,|\.)[0-9 ]*)?");

        if(re.exactMatch(input)){
            return QValidator::State::Intermediate;
        }else{
            return QValidator::State::Invalid;
        }
    }
}

