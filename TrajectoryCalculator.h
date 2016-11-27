#ifndef TAJECTORYCALCULATOR_H
#define TAJECTORYCALCULATOR_H

#include <cmath>
#include <vector>
#include <QTime>
#include "Point3DT.h"
#include "circuitparameters.h"
#include "Trajectory.h"
#include "trajectoryresulttype.h"
#include "partiallycalculatedcut.h"
#include "calculatedcut.h"
#include "tbb/tbb.h"
#include "crosssectiontype.h"
#include "exprtk/exprtk.hpp"

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

    //exprtk::parser<double> parser;

    Trajectory* calculateTrajectory(double i0, double u1_0, double u2_0);
    TrajectoryResultType::ResultType calculateTrajectoryResult(double i0, double u1_0, double u2_0, std::string chaosExpressionString, std::string LCExpressionString);
    CalculatedCut* calculateCut(CrossSectionType type, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, double z, std::string chaosExpressionString, std::string LCExpressionString);
    CalculatedCut* parallelCalculateCut(CrossSectionType type, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, double z, std::string chaosExpressionString, std::string LCExpressionString);

    bool hasPartialResult();
    PartiallyCalculatedCut* partialResult();

    exprtk::expression<double> createExpression(double* i, double* u1, double* u2);
    exprtk::expression<double> createCompiledExpression(double* i, double* u1, double* u2, std::string expressionString);
    bool isExpressionValid(std::string expressionString);

private:
    inline double fu1(double u1, double u2, double i);
    inline double fu2(double u1, double u2, double i);
    inline double fi(double u2, double i);
    inline double abs(double n);


    PartiallyCalculatedCut* currentResult = NULL;

};

#endif // TAJECTORYCALCULATOR_H

