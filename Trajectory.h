#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Point3DT.h"

class Trajectory
{
public:
    Trajectory(std::vector<Point3DT*>* points, int divisionCount);
    ~Trajectory();
    const std::vector<Point3DT*>* points;

    const int divisionCount;

    int getMaxMin();
    Point3DT getMaxMins();
    void writeToCSV(std::string filename);
    void writeToPLY(std::string filename, bool withEdges);
};

#endif // TRAJECTORY_H
