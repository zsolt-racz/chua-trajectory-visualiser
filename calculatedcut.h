#ifndef CALCULATEDCUT_H
#define CALCULATEDCUT_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "trajectoryresulttype.h"

class CalculatedCut
{

public:
    CalculatedCut(double i, double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step);

    struct TrajectoryResult{
        double u1;
        double u2;
        double t;

        TrajectoryResultType::ResultType result;
    };

    const double i;
    const int u1Size;
    const int u2Size;
    const double u1Min;
    const double u1Max;
    const double u2Min;
    const double u2Max;

    void writeToCSV(std::string filename);
    void writeToPLY(std::string filename);

    std::vector<std::vector<TrajectoryResult>>::iterator begin();
    std::vector<std::vector<TrajectoryResult>>::iterator end();

    std::vector<std::vector<TrajectoryResult>>::const_iterator cbegin();
    std::vector<std::vector<TrajectoryResult>>::const_iterator cend();

    CalculatedCut(double i, double u1Min, double u1Max, double u1Size, double u2Min, double u2Max, double u2Size, std::vector<std::vector<TrajectoryResult>> results);
protected:
    std::vector<std::vector<TrajectoryResult>> results;
};

#endif // CALCULATEDCUT_H
