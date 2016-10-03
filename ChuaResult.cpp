#include "ChuaResult.h"

ChuaResult::ChuaResult(std::vector<Point3DT*>* points, int divisionCount, ResultType resultType): points(points), divisionCount(divisionCount), resultType(resultType)
{

}

ChuaResult::~ChuaResult(){
    for (std::vector<Point3DT*>::const_iterator point = this->points->begin(); point != this->points->end(); ++point) {
        delete (*point);
    }
    delete points;
}

int ChuaResult::getMaxMin(){
    double maxMin = 0;
    const std::vector<Point3DT*>* points = this->points;
    for (std::vector<Point3DT*>::const_iterator point = points->begin(); point != points->end(); ++point) {
        if(maxMin < std::abs((*point)->i)){
            maxMin = std::abs((*point)->i);
        }
        if(maxMin < std::abs((*point)->u1)){
            maxMin = std::abs((*point)->u1);
        }
        if(maxMin < std::abs((*point)->u2)){
            maxMin = std::abs((*point)->u2);
        }
    }
    return (int) std::ceil(maxMin);
}

Point3DT ChuaResult::getMaxMins(){
    int iMaxMin = 0;
    int u1MaxMin = 0;
    int u2MaxMin = 0;
    int tMaxMin = 0;

    const std::vector<Point3DT*>* points = this->points;
    for (std::vector<Point3DT*>::const_iterator point = points->begin(); point != points->end(); ++point) {
        if(iMaxMin < std::abs((*point)->i)){
            iMaxMin = std::abs((*point)->i);
        }
        if(u1MaxMin < std::abs((*point)->u1)){
            u1MaxMin = std::abs((*point)->u1);
        }
        if(u2MaxMin < std::abs((*point)->u2)){
            u2MaxMin = std::abs((*point)->u2);
        }
        if(tMaxMin < std::abs((*point)->t)){
            tMaxMin = std::abs((*point)->t);
        }
    }
    return Point3DT(iMaxMin, u1MaxMin, u2MaxMin, tMaxMin);
}
