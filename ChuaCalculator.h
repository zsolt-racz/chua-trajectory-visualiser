#ifndef CHUACALCULATOR_H
#define CHUACALCULATOR_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Point3DT.h"

class ChuaCalculator {
public:
    ChuaCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max, double h);
    ~ChuaCalculator();

    const double C1;
    const double C2;
    const double L;
    const double Bp;
    const double B0;
    const double R;
    const double ro;
    const double I;
    const double m0;
    const double m1;
    const double m2;

    const double t_max;
    const double h;

    std::vector<Point3DT*>* calculateTrajectory(double i0, double u1_0, double u2_0);

    void writeToCSV(std::string filename, std::vector<Point3DT*>* points);
    void writeToPLY(std::string filename, std::vector<Point3DT*>* points, bool withEdges);
    void printEquations();
    void printParameters();

private:
    double fu1(double u1, double u2, double i);
    double fu2(double u1, double u2, double i);
    double fi(double u2, double i);
    void loadParameters(std::string filename);
};

#endif // CHUACALCULATOR_H

