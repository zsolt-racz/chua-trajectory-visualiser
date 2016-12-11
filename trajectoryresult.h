#ifndef TRAJECTORYRESULT_H
#define TRAJECTORYRESULT_H

struct TrajectoryResult{
    enum ResultType { UNDETERMINED = 6, LC = 0, CHA = 1 };

    double x;
    double y;
    double t;
    double divisionCount;

    ResultType result;
};

#endif // TRAJECTORYRESULT_H
