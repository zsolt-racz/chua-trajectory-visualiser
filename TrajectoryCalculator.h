#ifndef TAJECTORYCALCULATOR_H
#define TAJECTORYCALCULATOR_H

#include <cmath>
#include <vector>
#include <QElapsedTimer>
#include "Point3DT.h"
#include "circuitparameters.h"
#include "Trajectory.h"
#include "trajectoryresult.h"
#include "partiallycalculatedcrosssection.h"
#include "calculatedcrosssection.h"
#include "tbb/tbb.h"
#include "crosssectiontype.h"
#include "trajectorytest.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>

class TrajectoryCalculator{

public:
    TrajectoryCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max, double h0, double iStepMax, double uStepMax, double n, double t_test);
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
    const double n;
    const double t_test;
    bool cancelled = false;

    //exprtk::parser<double> parser;

    Trajectory* calculateTrajectory(double i0, double u1_0, double u2_0);
    Trajectory* calculateTrajectory(double i0, double u1_0, double u2_0, int saveNth, int maxPoints);
    void calculateTrajectoryResult(std::vector<TrajectoryResult>::iterator result, CrossSectionType type, double column, double row, double depth, std::vector<TrajectoryTest>* tests);
    CalculatedCrossSection* calculateCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests);
    CalculatedCrossSection* parallelCalculateCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests);

    bool hasPartialResult();
    PartiallyCalculatedCrossSection* partialResult();

private:
    inline double fu1(double u1, double u2, double i);
    inline double fu2(double u1, double u2, double i);
    inline double fi(double u2, double i);
    inline double abs(double n);


    PartiallyCalculatedCrossSection* currentResult = NULL;

};

#endif // TAJECTORYCALCULATOR_H

