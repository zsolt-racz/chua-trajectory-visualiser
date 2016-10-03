#include "ChuaCalculator.h"

ChuaCalculator::ChuaCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max,double h0, double iStepMax, double uStepMax) :
    C1(C1), C2(C2), L(L), Bp(Bp), B0(B0), R(R), ro(ro), I(I), m0(m0), m1(m1), m2(m2), t_max(t_max), h0(h0), iStepMax(iStepMax), uStepMax(uStepMax) {
}

ChuaCalculator::~ChuaCalculator() {
}

ChuaResult* ChuaCalculator::calculateTrajectory(double i0, double u1_0, double u2_0) {
    std::vector<Point3DT*>* points = new std::vector<Point3DT*>();

    double i = i0;
    double u1 = u1_0;
    double u2 = u2_0;

    double h = h0;

    int divisionCount = 0;
    ChuaResult::ResultType resultType = ChuaResult::UNDETERMINED;

    // Save initial coordinates at t=0
    points->push_back(new Point3DT(i0, u1_0, u2_0, 0));
    for (double t = h; t <= t_max; t += h) {
        double a_i = fi(u2, i);
        double a_u1 = fu1(u1, u2, i);
        double a_u2 = fu2(u1, u2, i);

        double b_i = fi(u2 + (h / 2) * a_u2, i + (h / 2) * a_i);
        double b_u1 = fu1(u1 + (h / 2) * a_u1, u2 + (h / 2) * a_u2, i + (h / 2) * a_i);
        double b_u2 = fu2(u1 + (h / 2) * a_u1, u2 + (h / 2) * a_u2, i + (h / 2) * a_i);

        double c_i = fi(u2 + (h / 2) * b_u2, i + (h / 2) * b_i);
        double c_u1 = fu1(u1 + (h / 2) * b_u1, u2 + (h / 2) * b_u2, i + (h / 2) * b_i);
        double c_u2 = fu2(u1 + (h / 2) * b_u1, u2 + (h / 2) * b_u2, i + (h / 2) * b_i);

        double d_i = fi(u2 + h * c_u2, i + h * c_i);
        double d_u1 = fu1(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);
        double d_u2 = fu2(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);

        double iDiff = (h / 6)*(a_i + 2 * b_i + 2 * c_i + d_i);
        double u1Diff = (h / 6)*(a_u1 + 2 * b_u1 + 2 * c_u1 + d_u1);
        double u2Diff = (h / 6)*(a_u2 + 2 * b_u2 + 2 * c_u2 + d_u2);

        if(std::abs(iDiff) > iStepMax || std::abs(u1Diff) > uStepMax || std::abs(u2Diff) > uStepMax){
            //std::cout << "Division by 2 at t = " << t << ". h = " << h << "\n";
            t = t - h;

            h = h / 2;
            divisionCount++;
        }else{
            i = i + iDiff;
            u1 = u1 + u1Diff;
            u2 = u2 + u2Diff;

            if(h != h0){
                h = h0;
            }

            points->push_back(new Point3DT(i, u1, u2, t));

            /* Test LC */
            if (u1 > 8 || u1 < -8) {
                resultType = ChuaResult::LC;
            }

            /* Test CHA */
            if (i < 0. && i > -0.5 && u2 < 0.227 && u2 > -0.18 && u1 > 0.5 && u1 < 1.) {
                resultType = ChuaResult::CHA;
            }
        }
    }



    std::cout << "Division count: " << divisionCount << "\n";

    return new ChuaResult(points, divisionCount, resultType);

}

void ChuaCalculator::writeToCSV(std::string filename, ChuaResult* result) {
    std::ofstream output;
    output.open(filename.c_str());

    const std::vector<Point3DT*>* points = result->points;
    for (std::vector<Point3DT*>::const_iterator point = points->begin(); point != points->end(); ++point) {
        output << std::setprecision(15) << (*point)->i << "; " << (*point)->u1 << "; " << (*point)->u2 << "; " << (*point)->t << "\n";
    }

    output.close();
}

void ChuaCalculator::writeToPLY(std::string filename, ChuaResult* result, bool withEdges) {
    std::ofstream output;
    output.open(filename.c_str());

    const std::vector<Point3DT*>* points = result->points;
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

    for (std::vector<Point3DT*>::const_iterator point = points->begin(); point != points->end(); ++point) {
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
    std::cout << "h0: " << h0 << "\n";
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

