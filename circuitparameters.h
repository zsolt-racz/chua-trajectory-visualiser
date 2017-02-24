#ifndef CIRCUITPARAMETERS_H
#define CIRCUITPARAMETERS_H

#include <QWidget>

class CircuitParameters
{
public:
    CircuitParameters(double C1, double C2, double R, double L, double I, double Bp, double B0, double m0, double m1, double m2, double ro, double t_max,double h0, double uStepMax, double iStepMax, double n, double t_test, double nth, double pMax);

    double C1 = 0;
    double C2 = 0;
    double R = 0;
    double L = 0;
    double I = 0;
    double Bp = 0;
    double B0 = 0;
    double m0 = 0;
    double m1 = 0;
    double m2 = 0;
    double ro = 0;
    double t_max = 0;
    double h0 = 0;
    double uStepMax = 0;
    double iStepMax = 0;
    double n = 2;
    double t_test = 0;
    int nth;
    int pMax;

};

#endif // CIRCUITPARAMETERS_H
