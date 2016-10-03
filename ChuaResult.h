#ifndef CHUARESULT_H
#define CHUARESULT_H

#include <vector>
#include <cmath>
#include "Point3DT.h"

class ChuaResult
{
public:
    enum ResultType { UNDETERMINED, LC, CHA };

    ChuaResult(std::vector<Point3DT*>* points, int divisionCount, ResultType resultType);
    ~ChuaResult();
    const std::vector<Point3DT*>* points;

    const int divisionCount;
    const ResultType resultType;

    int getMaxMin();
    Point3DT getMaxMins();
};

#endif // CHUARESULT_H
