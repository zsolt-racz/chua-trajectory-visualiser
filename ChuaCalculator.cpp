#include "ChuaCalculator.h"

ChuaCalculator::ChuaCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max, double h) :
    C1(C1), C2(C2), L(L), Bp(Bp), B0(B0), R(R), ro(ro), I(I), m0(m0), m1(m1), m2(m2), t_max(t_max), h(h) {
}

ChuaCalculator::~ChuaCalculator() {
}

std::vector<Point3DT*>* ChuaCalculator::calculateTrajectory(double i0, double u1_0, double u2_0) {
    std::vector<Point3DT*>* result = new std::vector<Point3DT*>();

    double i = i0;
    double u1 = u1_0;
    double u2 = u2_0;

    double a_i, a_u1, a_u2;
    double b_i, b_u1, b_u2;
    double c_i, c_u1, c_u2;
    double d_i, d_u1, d_u2;

    double t;
    for (t = 0; t <= t_max; t += h) {
        result->push_back(new Point3DT(i, u1, u2, t));

        a_i = fi(u2, i);
        a_u1 = fu1(u1, u2, i);
        a_u2 = fu2(u1, u2, i);

        b_i = fi(u2 + (h / 2) * a_u2, i + (h / 2) * a_i);
        b_u1 = fu1(u1 + (h / 2) * a_u1, u2 + (h / 2) * a_u2, i + (h / 2) * a_i);
        b_u2 = fu2(u1 + (h / 2) * a_u1, u2 + (h / 2) * a_u2, i + (h / 2) * a_i);

        c_i = fi(u2 + (h / 2) * b_u2, i + (h / 2) * b_i);
        c_u1 = fu1(u1 + (h / 2) * b_u1, u2 + (h / 2) * b_u2, i + (h / 2) * b_i);
        c_u2 = fu2(u1 + (h / 2) * b_u1, u2 + (h / 2) * b_u2, i + (h / 2) * b_i);

        d_i = fi(u2 + h * c_u2, i + h * c_i);
        d_u1 = fu1(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);
        d_u2 = fu2(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);


        i = i + (h / 6)*(a_i + 2 * b_i + 2 * c_i + d_i);
        u1 = u1 + (h / 6)*(a_u1 + 2 * b_u1 + 2 * c_u1 + d_u1);
        u2 = u2 + (h / 6)*(a_u2 + 2 * b_u2 + 2 * c_u2 + d_u2);
    }

    return result;
}

void ChuaCalculator::writeToCSV(std::string filename, std::vector<Point3DT*>* points) {
    std::ofstream output;
    output.open(filename.c_str());

    for (std::vector<Point3DT*>::iterator point = points->begin(); point != points->end(); ++point) {
        output << (*point)->i << ", " << (*point)->u1 << ", " << (*point)->u2 << ", " << (*point)->t << "\n";
    }

    output.close();
}

void ChuaCalculator::writeToPLY(std::string filename, std::vector<Point3DT*>* points, bool withEdges) {
    std::ofstream output;
    output.open(filename.c_str());

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

    for (std::vector<Point3DT*>::iterator point = points->begin(); point != points->end(); ++point) {
        output << (*point)->i << " " << (*point)->u1 << " " << (*point)->u2 << "\n";
    }

    if (withEdges) {
        for (unsigned int i = 0; i < points->size() - 1; i++) {
            output << "2 " << i << " " << i + 1 << "\n";
        }
    }

    output.close();
}

void ChuaCalculator::printEquations() {
    std::cout << "1.: " << C1 << "du1/dt = (u2-u1)/" << R << " - g(u1) - 0" << "\n";
    std::cout << "2.: " << C2 << "du2/dt = (u1-u2)/R" << R << " +i" << "\n";
    std::cout << "3.: " << L << "di/dt  = " << "u2 - " << ro << "i" << "\n";
}

void ChuaCalculator::printParameters() {
    std::cout << "C1: " << C1 << "\n";
    std::cout << "C2: " << C2 << "\n";
    std::cout << "L: " << L << "\n";
    std::cout << "Bp: " << Bp << "\n";
    std::cout << "B0: " << B0 << "\n";
    std::cout << "R: " << R << "\n";
    std::cout << "ro: " << ro << "\n";
    std::cout << "I: " << I << "\n";
    std::cout << "m0: " << m0 << "\n";
    std::cout << "m1: " << m1 << "\n";
    std::cout << "m2: " << m2 << "\n";
    std::cout << "t_max: " << t_max << "\n";
    std::cout << "h: " << h << "\n";
}

double ChuaCalculator::fu1(double u1, double u2, double i) {
    return ((u2 - u1) / R - (m2 * u1 + 0.5 * (m1 - m0)*(std::abs(u1 - Bp) - std::abs(u1 + Bp)) + 0.5 * (m2 - m1)*(std::abs(u1 - B0) - std::abs(u1 + B0))) - I) / C1;
}

double ChuaCalculator::fu2(double u1, double u2, double i) {
    return ((u1 - u2) / R + i) / C2;
}

double ChuaCalculator::fi(double u2, double i) {
    return (-u2 - ro * i) / L;
}

