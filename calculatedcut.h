#ifndef CALCULATEDCUT_H
#define CALCULATEDCUT_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "crosssectiontype.h"
#include "trajectoryresulttype.h"

class CalculatedCut
{

public:
    CalculatedCut(CrossSectionType type, double i, double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step);

    struct TrajectoryResult{
        double x;
        double y;
        double t;

        TrajectoryResultType::ResultType result;
    };

    CrossSectionType type;
    const double i;
    const double u1Min;
    const double u1Max;
    const int u1Size;
    const double u2Min;
    const double u2Max;
    const int u2Size;

    void writeToCSV(std::string filename);
    void writeToPLY(std::string filename);

    std::vector<std::vector<TrajectoryResult>>::iterator begin();
    std::vector<std::vector<TrajectoryResult>>::iterator end();

    std::vector<std::vector<TrajectoryResult>>::const_iterator cbegin();
    std::vector<std::vector<TrajectoryResult>>::const_iterator cend();

    CalculatedCut(CrossSectionType type, double i, double u1Min, double u1Max, double u1Size, double u2Min, double u2Max, double u2Size, std::vector<std::vector<TrajectoryResult>> results);
protected:
    std::vector<std::vector<TrajectoryResult>> results;
};

#endif // CALCULATEDCUT_H
