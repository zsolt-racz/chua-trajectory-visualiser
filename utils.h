#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QLocale>
#include <QRegExp>
#include <iostream>

class Utils
{
public:
    Utils();

    static QString formatNumber(double value);
    static QString formatNumber(double value, int precision);
    static QString formatNumber(int value);
    static double parseDouble(const QString text);
    static int parseInt(const QString text);
};

#endif // UTILS_H
