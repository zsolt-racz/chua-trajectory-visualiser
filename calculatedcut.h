#ifndef CALCULATEDCUT_H
#define CALCULATEDCUT_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "crosssectiontype.h"
#include "trajectoryresult.h"
#include "trajectoryresulttype.h"

class CalculatedCut
{

public:
    CalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, std::vector<TrajectoryTest>* tests);
    ~CalculatedCut();
    CrossSectionType type;
    const double z;
    const double xMin;
    const double xMax;
    const int xSize;
    const double yMin;
    const double yMax;
    const int ySize;

    void writeToTxt(std::string filename);

    std::vector<std::vector<TrajectoryResult>>::iterator begin();
    std::vector<std::vector<TrajectoryResult>>::iterator end();

    std::vector<std::vector<TrajectoryResult>>::const_iterator cbegin();
    std::vector<std::vector<TrajectoryResult>>::const_iterator cend();
    int getTestIndex(const TrajectoryTest test);
    int getTestIndex(const TrajectoryTest* test);

    CalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xSize, double yMin, double yMax, double ySize, std::vector<TrajectoryTest>* tests, std::vector<std::vector<TrajectoryResult>> results);
protected:
    std::vector<TrajectoryTest>* tests;
    std::vector<std::vector<TrajectoryResult>> results;

};

#endif // CALCULATEDCUT_H
