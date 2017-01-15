#ifndef TRAJECTORYTEST_H
#define TRAJECTORYTEST_H

#include <string>
#include "trajectoryresulttype.h"

class TrajectoryTest
{
public:

    TrajectoryTest(std::string name, TrajectoryResultType type, std::string color, double u1Lo, double u1Hi, double u2Lo, double u2Hi, double iLo, double iHi);
    bool operator==(const TrajectoryTest& tt) const;

    const std::string name;
    const TrajectoryResultType type;
    const std::string color;

    const double u1Lo;
    const double u1Hi;
    const double u2Lo;
    const double u2Hi;
    const double iLo;
    const double iHi;

    bool eval(double u1, double u2, double i) const;
    bool isChaos() const;
    bool isLC() const;

};

#endif // TRAJECTORYTEST_H
