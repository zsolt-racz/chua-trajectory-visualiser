#ifndef TAJECTORYCALCULATOR_H
#define TAJECTORYCALCULATOR_H

#include <cmath>
#include <vector>
#include "Point3DT.h"
#include "circuitparameters.h"
#include "Trajectory.h"

class TrajectoryCalculator {
public:
    enum ResultType { UNDETERMINED, LC, CHA };

    TrajectoryCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max, double h0, double iStepMax, double uStepMax);
    TrajectoryCalculator(CircuitParameters* parameters);
    ~TrajectoryCalculator();

    const double C1;
    const double C2;
    const double L;
    const double Bp;
    const double B0;
    const double R;
    const double ro;
    const double I;
    const double m0;
    const double m1;
    const double m2;
    const double t_max;
    const double h0;
    const double iStepMax;
    const double uStepMax;

    Trajectory* calculateTrajectory(double i0, double u1_0, double u2_0);
    ResultType calculateTrajectoryResult(double i0, double u1_0, double u2_0);
    std::vector<std::vector<ResultType>*>* calculateCut(double u1Min, double u1Max, double u1Step,double u2Min, double u2Max, double u2Step, double i);

private:
    double fu1(double u1, double u2, double i);
    double fu2(double u1, double u2, double i);
    double fi(double u2, double i);
};

#endif // TAJECTORYCALCULATOR_H

