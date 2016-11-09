#ifndef TAJECTORYCALCULATOR_H
#define TAJECTORYCALCULATOR_H

#include <cmath>
#include <vector>
#include "Point3DT.h"
#include "circuitparameters.h"
#include "Trajectory.h"
#include "trajectoryresulttype.h"
#include "partiallycalculatedcut.h"
#include "calculatedcut.h"
#include "tbb/tbb.h"
#include "crosssectiontype.h"

class TrajectoryCalculator{

public:
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
    TrajectoryResultType::ResultType calculateTrajectoryResult(double i0, double u1_0, double u2_0);
    CalculatedCut* calculateCut(CrossSectionType type, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, double z);
    CalculatedCut* parallelCalculateCut(CrossSectionType type, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, double z);

    bool hasPartialResult();
    PartiallyCalculatedCut* partialResult();

private:
    inline double fu1(double u1, double u2, double i);
    inline double fu2(double u1, double u2, double i);
    inline double fi(double u2, double i);
    inline double abs(double n);


    PartiallyCalculatedCut* currentResult = NULL;

};

#endif // TAJECTORYCALCULATOR_H

