#include "Trajectory.h"

Trajectory::Trajectory(std::vector<Point3DT>* points, int divisionCount): points(points), divisionCount(divisionCount)
{

}

Trajectory::~Trajectory(){
    delete points;
}

int Trajectory::getMaxMin(){
    double maxMin = 0;
    const std::vector<Point3DT>* points = this->points;
    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        if(maxMin < std::abs(point->i)){
            maxMin = std::abs(point->i);
        }
        if(maxMin < std::abs(point->u1)){
            maxMin = std::abs(point->u1);
        }
        if(maxMin < std::abs(point->u2)){
            maxMin = std::abs(point->u2);
        }
    }
    return (int) std::ceil(maxMin);
}

Point3DT Trajectory::getMaxMins(){
    Point3DT maxes = this->getMaxes();
    Point3DT mins = this->getMins();

    return Point3DT(std::max(std::abs(maxes.i), std::abs(mins.i)), std::max(std::abs(maxes.u1), std::abs(mins.u1)), std::max(std::abs(maxes.u2), std::abs(mins.u2)), std::max(std::abs(maxes.t), std::abs(mins.t)));
}

Point3DT Trajectory::getMaxes(){
    if(this->points->size() == 0){
        return Point3DT(0, 0, 0, 0);
    }

    double iMax = std::numeric_limits<double>::min();
    double u1Max = std::numeric_limits<double>::min();
    double u2Max = std::numeric_limits<double>::min();
    double tMax = std::numeric_limits<double>::min();

    const std::vector<Point3DT>* points = this->points;
    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        if(iMax < point->i){
            iMax = point->i;
        }
        if(u1Max < point->u1){
            u1Max = point->u1;
        }
        if(u2Max < point->u2){
            u2Max = point->u2;
        }
        if(tMax < point->t){
            tMax = point->t;
        }
    }
    return Point3DT(iMax, u1Max, u2Max, tMax);
}

Point3DT Trajectory::getMins(){
    if(this->points->size() == 0){
        return Point3DT(0, 0, 0, 0);
    }

    double iMin = std::numeric_limits<double>::max();
    double u1Min = std::numeric_limits<double>::max();
    double u2Min = std::numeric_limits<double>::max();
    double tMin = std::numeric_limits<double>::max();

    const std::vector<Point3DT>* points = this->points;
    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        if(iMin > point->i){
            iMin = point->i;
        }
        if(u1Min > point->u1){
            u1Min = point->u1;
        }
        if(u2Min > point->u2){
            u2Min = point->u2;
        }
        if(tMin > point->t){
            tMin = point->t;
        }
    }
    return Point3DT(iMin, u1Min, u2Min, tMin);
}


void Trajectory::writeToTXT(std::string filename, std::string separator) {
    std::ofstream output;
    output.open(filename.c_str());

    const std::vector<Point3DT>* points = this->points;
    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        output << std::setprecision(15) << point->i << separator << point->u2 << separator << point->u1 << separator << point->t << "\n";
    }

    output.close();
}

void Trajectory::writeToPLY(std::string filename, bool withEdges) {
    std::ofstream output;
    output.open(filename.c_str());

    const std::vector<Point3DT>* points = this->points;
    output << "ply" << "\n";
    output << "format ascii 1.0" << "\n";
    output << "element vertex " << points->size() << "\n";
    output << "property float x" << "\n";
    output << "property float y" << "\n";
    output << "property float z" << "\n";
    if (withEdges) {
        output << "element edge " << points->size() - 1 << "\n";
        output << "property int vertex1 \n";
        output << "property int vertex2 \n";
    }
    output << "end_header" << "\n";

    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        output << point->i << " " << point->u2 << " " << point->u1 << "\n";
    }

    if (withEdges) {
        for (unsigned int i = 0; i < points->size() - 1; i++) {
            output << "2 " << i << " " << i + 1 << "\n";
        }
    }

    output.close();
}
