#ifndef PARTIALLYCALCULATEDCUT_H
#define PARTIALLYCALCULATEDCUT_H

#include <list>
#include <vector>
#include "calculatedcut.h"

class PartiallyCalculatedCut : public CalculatedCut
{

public:
    PartiallyCalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, std::vector<TrajectoryTest>* tests);

    std::list<std::vector<TrajectoryResult>*>::const_iterator cbeginXColumns();
    std::list<std::vector<TrajectoryResult>*>::const_iterator cendXColumns();
    std::size_t XCount();
    void addXColumn(std::vector<TrajectoryResult>* x);

    double progress();

private:
    std::list<std::vector<TrajectoryResult>*> calculatedXColumns;
    int currentProgress;
};

#endif // PARTIALLYCALCULATEDCUT_H
