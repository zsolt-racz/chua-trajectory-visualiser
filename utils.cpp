#include "utils.h"

Utils::Utils()
{

}

QString Utils::formatNumber(double value, int precision){
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    QString s = locale.toString(value, 'f', precision);
    s.replace(locale.groupSeparator(), ' ');
    s.replace(locale.decimalPoint(), '.');

    s.remove( QRegExp("0+$") );
    s.remove( QRegExp("\\.$") );

    return s;
}

QString Utils::formatNumber(double value){
    return Utils::formatNumber(value, 15);
}

QString Utils::formatNumber(int value){
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    QString s = locale.toString(value);
    s.replace(locale.groupSeparator(), ' ');
    return s;
}

double Utils::parseDouble(const QString text){
    QLocale locale(QLocale::English, QLocale::UnitedStates);

    QString s(text);
    s.replace('.', locale.decimalPoint());
    s.replace(',', locale.decimalPoint());
    s.remove(' ');

    return locale.toDouble(s);
}

int Utils::parseInt(const QString text){
    QLocale locale(QLocale::English, QLocale::UnitedStates);

    QString s(text);
    s.remove(' ');
    int result = locale.toInt(s);

    return result;
}
