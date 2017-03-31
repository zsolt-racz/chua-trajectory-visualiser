#ifndef TRAJECTORYRESULT_H
#define TRAJECTORYRESULT_H

#include "trajectorytest.h"
#include "trajectoryresulttype.h"

struct TrajectoryResult{
    double column;
    double row;
    const TrajectoryTest* test = NULL;
    double t;
    double divisionCount;

    TrajectoryResultType result() const;
};

#endif // TRAJECTORYRESULT_H
