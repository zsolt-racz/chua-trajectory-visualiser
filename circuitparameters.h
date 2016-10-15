#ifndef CIRCUITPARAMETERS_H
#define CIRCUITPARAMETERS_H

#include <QWidget>
#include <fstream>
#include <iomanip>

class CircuitParameters
{
public:
    CircuitParameters(std::string fileName);
    CircuitParameters(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max,double h0, double iStepMax, double uStepMax);

    double C1 = 0;
    double C2 = 0;
    double L= 0;
    double Bp = 0;
    double B0 = 0;
    double R = 0;
    double ro = 0;
    double I = 0;
    double m0 = 0;
    double m1 = 0;
    double m2 = 0;
    double t_max = 0;
    double h0 = 0;
    double iStepMax = 0;
    double uStepMax = 0;

    void loadFromFile(std::string fileName);
    void saveToFile(std::string fileName);
};

#endif // CIRCUITPARAMETERS_H
