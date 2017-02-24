#include "circuitparameters.h"

CircuitParameters::CircuitParameters(double C1, double C2, double R, double L, double I, double Bp, double B0, double m0, double m1, double m2, double ro, double t_max,double h0, double uStepMax, double iStepMax, double n, double t_test, double nth, double pMax) :
    C1(C1), C2(C2), R(R), L(L), I(I), Bp(Bp), B0(B0), m0(m0), m1(m1), m2(m2), ro(ro), t_max(t_max), h0(h0), uStepMax(uStepMax), iStepMax(iStepMax), n(n), t_test(t_test), nth(nth), pMax(pMax) {
}
