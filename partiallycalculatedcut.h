#ifndef PARTIALLYCALCULATEDCUT_H
#define PARTIALLYCALCULATEDCUT_H

#include <list>
#include "calculatedcut.h"

class PartiallyCalculatedCut : public CalculatedCut
{

public:
    PartiallyCalculatedCut(double i, double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step);

    std::list<std::vector<CalculatedCut::TrajectoryResult>*>::const_iterator cbeginU1Columns();
    std::list<std::vector<CalculatedCut::TrajectoryResult>*>::const_iterator cendU1Columns();
    std::size_t U1Count();
    void addU1Column(std::vector<CalculatedCut::TrajectoryResult>* u1);

    CalculatedCut* createCalculatedCut();
    double progress();

private:
    std::list<std::vector<CalculatedCut::TrajectoryResult>*> calculatedU1Columns;
    int currentProgress;
};

#endif // PARTIALLYCALCULATEDCUT_H
