#ifndef PARTIALLYCALCULATEDCROSSSECTION_H
#define PARTIALLYCALCULATEDCROSSSECTION_H

#include <list>
#include <vector>
#include "calculatedcrosssection.h"

class PartiallyCalculatedCrossSection : public CalculatedCrossSection
{

public:
    PartiallyCalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests);

    std::list<std::vector<TrajectoryResult>*>::const_iterator cbeginColumns();
    std::list<std::vector<TrajectoryResult>*>::const_iterator cendColumns();
    void addColumn(std::vector<TrajectoryResult>* column);

    double progress();

private:
    std::list<std::vector<TrajectoryResult>*> calculatedColumns;
    int currentProgress;
};

#endif // PARTIALLYCALCULATEDCROSSSECTION_H
