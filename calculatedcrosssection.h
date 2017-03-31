#ifndef CALCULATEDCROSSSECTION_H
#define CALCULATEDCROSSSECTION_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "crosssectiontype.h"
#include "trajectoryresult.h"
#include "trajectoryresulttype.h"

class CalculatedCrossSection
{

public:
    CalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests);
    CalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests, std::vector<std::vector<TrajectoryResult>> results);
    CalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, std::vector<TrajectoryTest>* tests, std::string filePath);
    ~CalculatedCrossSection();
    CrossSectionType type;
    double depth;

    double columnMin;
    double columnMax;
    int columnCount;
    double rowMin;
    double rowMax;
    int rowCount;

    void writeToTxt(std::string filename, std::string separator);

    std::vector<std::vector<TrajectoryResult>>::iterator begin();
    std::vector<std::vector<TrajectoryResult>>::iterator end();

    std::vector<std::vector<TrajectoryResult>>::const_iterator cbegin();
    std::vector<std::vector<TrajectoryResult>>::const_iterator cend();
    int getTestIndex(const TrajectoryTest test);
    int getTestIndex(const TrajectoryTest* test);
protected:
    std::vector<TrajectoryTest>* tests;
    std::vector<std::vector<TrajectoryResult>> results;

};

#endif // CALCULATEDCROSSSECTION_H
