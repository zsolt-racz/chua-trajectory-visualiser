#ifndef PARTIALLYCALCULATEDCUT_H
#define PARTIALLYCALCULATEDCUT_H

#include <list>
#include <vector>
#include "calculatedcut.h"

class PartiallyCalculatedCut : public CalculatedCut
{

public:
    PartiallyCalculatedCut(CrossSectionType type, double i, double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step, std::vector<TrajectoryTest>* tests);

    std::list<std::vector<TrajectoryResult>*>::const_iterator cbeginU1Columns();
    std::list<std::vector<TrajectoryResult>*>::const_iterator cendU1Columns();
    std::size_t U1Count();
    void addU1Column(std::vector<TrajectoryResult>* u1);

    double progress();

private:
    std::list<std::vector<TrajectoryResult>*> calculatedU1Columns;
    int currentProgress;
};

#endif // PARTIALLYCALCULATEDCUT_H
