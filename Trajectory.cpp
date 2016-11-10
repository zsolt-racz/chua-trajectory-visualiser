#include "Trajectory.h"

Trajectory::Trajectory(std::vector<Point3DT>* points, int divisionCount): points(points), divisionCount(divisionCount)
{

}

Trajectory::~Trajectory(){
    std::cout << "destructing trajectory\n";
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
    int iMaxMin = 0;
    int u1MaxMin = 0;
    int u2MaxMin = 0;
    int tMaxMin = 0;

    const std::vector<Point3DT>* points = this->points;
    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        if(iMaxMin < std::abs(point->i)){
            iMaxMin = std::abs(point->i);
        }
        if(u1MaxMin < std::abs(point->u1)){
            u1MaxMin = std::abs(point->u1);
        }
        if(u2MaxMin < std::abs(point->u2)){
            u2MaxMin = std::abs(point->u2);
        }
        if(tMaxMin < std::abs(point->t)){
            tMaxMin = std::abs(point->t);
        }
    }
    return Point3DT(iMaxMin, u1MaxMin, u2MaxMin, tMaxMin);
}


void Trajectory::writeToCSV(std::string filename) {
    std::ofstream output;
    output.open(filename.c_str());

    const std::vector<Point3DT>* points = this->points;
    for (std::vector<Point3DT>::const_iterator point = points->begin(); point != points->end(); ++point) {
        output << std::setprecision(15) << point->i << "; " << point->u1 << "; " << point->u2 << "; " << point->t << "\n";
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
        output << point->i << " " << point->u1 << " " << point->u2 << "\n";
    }

    if (withEdges) {
        for (unsigned int i = 0; i < points->size() - 1; i++) {
            output << "2 " << i << " " << i + 1 << "\n";
        }
    }

    output.close();
}
