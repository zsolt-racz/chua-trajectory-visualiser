#include "TrajectoryCalculator.h"

TrajectoryCalculator::TrajectoryCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max,double h0, double iStepMax, double uStepMax) :
    C1(C1), C2(C2), L(L), Bp(Bp), B0(B0), R(R), ro(ro), I(I), m0(m0), m1(m1), m2(m2), t_max(t_max), h0(h0), iStepMax(iStepMax), uStepMax(uStepMax) {
}

TrajectoryCalculator::TrajectoryCalculator(CircuitParameters* parameters) :
    C1(parameters->C1), C2(parameters->C2), L(parameters->L), Bp(parameters->Bp), B0(parameters->B0), R(parameters->R), ro(parameters->ro), I(parameters->I), m0(parameters->m0), m1(parameters->m1), m2(parameters->m2), t_max(parameters->t_max), h0(parameters->h0), iStepMax(parameters->iStepMax), uStepMax(parameters->uStepMax) {
}

TrajectoryCalculator::~TrajectoryCalculator() {
}

Trajectory* TrajectoryCalculator::calculateTrajectory(double i0, double u1_0, double u2_0) {
    std::vector<Point3DT*>* points = new std::vector<Point3DT*>();

    double i = i0;
    double u1 = u1_0;
    double u2 = u2_0;

    double h = h0;

    int divisionCount = 0;
    ResultType resultType = UNDETERMINED;

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
                resultType = LC;
            }

            /* Test CHA */
            if (i < 0. && i > -0.5 && u2 < 0.227 && u2 > -0.18 && u1 > 0.5 && u1 < 1.) {
                resultType = CHA;
            }
        }
    }


    return new Trajectory(points, divisionCount);
}

TrajectoryCalculator::ResultType TrajectoryCalculator::calculateTrajectoryResult(double i0, double u1_0, double u2_0) {
    double i = i0;
    double u1 = u1_0;
    double u2 = u2_0;

    double h = h0;

    ResultType resultType = UNDETERMINED;

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
        }else{
            i = i + iDiff;
            u1 = u1 + u1Diff;
            u2 = u2 + u2Diff;

            if(h != h0){
                h = h0;
            }

            /* Test LC */
            if (u1 > 8 || u1 < -8) {
                resultType = LC;
            }

            /* Test CHA */
            if (i < 0. && i > -0.5 && u2 < 0.227 && u2 > -0.18 && u1 > 0.5 && u1 < 1.) {
                resultType = CHA;
            }
        }
    }

    return resultType;
}

std::vector<std::vector<TrajectoryCalculator::ResultType>*>* TrajectoryCalculator::calculateCut(double u1Min, double u1Max, double u1Step,double u2Min, double u2Max, double u2Step, double i){
    std::vector<std::vector<TrajectoryCalculator::ResultType>*>* result = new std::vector<std::vector<TrajectoryCalculator::ResultType>*>();
    for(double u1 = u1Min; u1<=u1Max; u1+=u1Step){
        std::vector<TrajectoryCalculator::ResultType>* row = new std::vector<TrajectoryCalculator::ResultType>;
        for(double u2 = u2Min; u2<=u2Max; u2+=u2Step){
            row->push_back(this->calculateTrajectoryResult(i, u1, u2));
        }
        result->push_back(row);
    }

    return result;
}

double TrajectoryCalculator::fu1(double u1, double u2, double i) {
    return ((u2 - u1) / R - (m2 * u1 + 0.5 * (m1 - m0)*(std::abs(u1 - Bp) - std::abs(u1 + Bp)) + 0.5 * (m2 - m1)*(std::abs(u1 - B0) - std::abs(u1 + B0))) - I) / C1;
}

double TrajectoryCalculator::fu2(double u1, double u2, double i) {
    return ((u1 - u2) / R + i) / C2;
}

double TrajectoryCalculator::fi(double u2, double i) {
    return (-u2 - ro * i) / L;
}

