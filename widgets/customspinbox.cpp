#include "customspinbox.h"

CustomSpinBox::CustomSpinBox(QWidget *parent) :
    QSpinBox(parent)
{

}

CustomSpinBox::~CustomSpinBox()
{

}

QString CustomSpinBox::textFromValue(int value) const
{
    return Utils::formatNumber(value);
}

int CustomSpinBox::valueFromText(const QString &text) const
{
    return Utils::parseInt(text);
}

QValidator::State CustomSpinBox::validate(QString &input, int &pos) const
{
    QRegExp re("[+-]?[0-9 ]+");

    if(re.exactMatch(input)){
        return QValidator::State::Acceptable;
    }else{
        QRegExp re("[+-]?[0-9 ]*");

        if(re.exactMatch(input)){
            return QValidator::State::Intermediate;
        }else{
            return QValidator::State::Invalid;
        }
    }
}

