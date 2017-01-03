#include "TrajectoryCalculator.h"

TrajectoryCalculator::TrajectoryCalculator(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max,double h0, double iStepMax, double uStepMax, double n, double t_test) :
    C1(C1), C2(C2), L(L), Bp(Bp), B0(B0), R(R), ro(ro), I(I), m0(m0), m1(m1), m2(m2), t_max(t_max), h0(h0), iStepMax(iStepMax), uStepMax(uStepMax), n(n), t_test(t_test) {
}

TrajectoryCalculator::TrajectoryCalculator(CircuitParameters* parameters) :
    C1(parameters->C1), C2(parameters->C2), L(parameters->L), Bp(parameters->Bp), B0(parameters->B0), R(parameters->R), ro(parameters->ro), I(parameters->I), m0(parameters->m0), m1(parameters->m1), m2(parameters->m2), t_max(parameters->t_max), h0(parameters->h0), iStepMax(parameters->iStepMax), uStepMax(parameters->uStepMax), n(parameters->n), t_test(parameters->t_test) {
}

TrajectoryCalculator::~TrajectoryCalculator() {
}

Trajectory* TrajectoryCalculator::calculateTrajectory(double i0, double u1_0, double u2_0) {
    std::vector<Point3DT>* points = new std::vector<Point3DT>();

    double i = i0;
    double u1 = u1_0;
    double u2 = u2_0;

    double h = h0;

    int divisionCount = 0;

    // Save initial coordinates at t=0
    points->push_back(Point3DT(i0, u1_0, u2_0, 0));
    for (double t = h; t <= t_max; t += h) {
        double a_i = fi(u2, i);
        double a_u1 = fu1(u1, u2, i);
        double a_u2 = fu2(u1, u2, i);
        double hdiv2 = 0.5 * h;
        double hdiv6 = h/6;

        double b_i = fi(u2 + hdiv2 * a_u2, i + hdiv2 * a_i);
        double b_u1 = fu1(u1 + hdiv2 * a_u1, u2 + hdiv2 * a_u2, i + hdiv2 * a_i);
        double b_u2 = fu2(u1 + hdiv2 * a_u1, u2 + hdiv2 * a_u2, i + hdiv2 * a_i);

        double c_i = fi(u2 + hdiv2* b_u2, i + hdiv2 * b_i);
        double c_u1 = fu1(u1 + hdiv2 * b_u1, u2 + hdiv2 * b_u2, i + hdiv2 * b_i);
        double c_u2 = fu2(u1 + hdiv2 * b_u1, u2 + hdiv2 * b_u2, i + hdiv2 * b_i);

        double d_i = fi(u2 + h * c_u2, i + h * c_i);
        double d_u1 = fu1(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);
        double d_u2 = fu2(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);

        double iDiff = hdiv6*(a_i + 2 * b_i + 2 * c_i + d_i);
        double u1Diff = hdiv6*(a_u1 + 2 * b_u1 + 2 * c_u1 + d_u1);
        double u2Diff = hdiv6*(a_u2 + 2 * b_u2 + 2 * c_u2 + d_u2);

        if(this->abs(iDiff) > iStepMax || this->abs(u1Diff) > uStepMax || this->abs(u2Diff) > uStepMax){
            //std::cout << "Division by 2 at t = " << t << ". h = " << h << "\n";
            t = t - h;

            h = h / 2;
            ++divisionCount;
        }else{
            i = i + iDiff;
            u1 = u1 + u1Diff;
            u2 = u2 + u2Diff;

            h = h * this->n;

            points->push_back(Point3DT(i, u1, u2, t));
        }
    }

    return new Trajectory(points, divisionCount);
}


void TrajectoryCalculator::calculateTrajectoryResult(std::vector<TrajectoryResult>::iterator result, CrossSectionType type, double x, double y, double z, std::vector<TrajectoryTest>* tests) {
    result->x = x;
    result->y = y;

    int divisionCount = 0;

    double i,u1,u2;

    switch (type) {
        case U1_I:
            i = y; u1 = x; u2 = z;
            break;
        case U2_I:
            i = y; u1 = z; u2 = x;
            break;
        case U1_U2:
            i = z; u1 = x; u2 = y;
            break;
    }

    double h = h0;
    double t;

    for (t = h; t <= t_max; t += h) {
        double a_i = fi(u2, i);
        double a_u1 = fu1(u1, u2, i);
        double a_u2 = fu2(u1, u2, i);
        double hdiv2 = h/2;
        double hdiv6 = h/6;

        double b_i = fi(u2 + hdiv2 * a_u2, i + hdiv2 * a_i);
        double b_u1 = fu1(u1 + hdiv2 * a_u1, u2 + hdiv2 * a_u2, i + hdiv2 * a_i);
        double b_u2 = fu2(u1 + hdiv2 * a_u1, u2 + hdiv2 * a_u2, i + hdiv2 * a_i);

        double c_i = fi(u2 + hdiv2 * b_u2, i + hdiv2 * b_i);
        double c_u1 = fu1(u1 + hdiv2 * b_u1, u2 + hdiv2 * b_u2, i + hdiv2 * b_i);
        double c_u2 = fu2(u1 + hdiv2 * b_u1, u2 + hdiv2 * b_u2, i + hdiv2 * b_i);

        double d_i = fi(u2 + h * c_u2, i + h * c_i);
        double d_u1 = fu1(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);
        double d_u2 = fu2(u1 + h * c_u1, u2 + h * c_u2, i + h * c_i);
        double iDiff = hdiv6*(a_i + 2 * b_i + 2 * c_i + d_i);
        double u1Diff = hdiv6*(a_u1 + 2 * b_u1 + 2 * c_u1 + d_u1);
        double u2Diff = hdiv6*(a_u2 + 2 * b_u2 + 2 * c_u2 + d_u2);

        if(this->abs(iDiff) > iStepMax || this->abs(u1Diff) > uStepMax || this->abs(u2Diff) > uStepMax){
            //std::cout << "Division by 2 at t = " << t << ". h = " << h << "\n";
            t = t - h;

            h = h / 2;
            ++divisionCount;
        }else{
            i = i + iDiff;
            u1 = u1 + u1Diff;
            u2 = u2 + u2Diff;

            h = h * this->n;

            // Tests
            if(t > 50){
                for(std::vector<TrajectoryTest>::const_iterator test = tests->cbegin(); test != tests->cend(); ++test){
                    if(test->eval(u1, u2, i)){
                        result->t = t;
                        result->test = &(*test);
                        result->divisionCount = divisionCount;

                        return;
                    }
                }
            }
        }
    }

    result->t = t;
    result->divisionCount = divisionCount;
}

CalculatedCut* TrajectoryCalculator::calculateCrossSection(CrossSectionType type, double xMin, double xMax, double xStep,double yMin, double yMax, double yStep, double z, std::vector<TrajectoryTest>* tests){
    this->currentResult = new PartiallyCalculatedCut(type, z, xMin, xMax, xStep, yMin, yMax, yStep, tests);

    std::vector<std::vector<TrajectoryResult>>::iterator vector_iterator = currentResult->begin();
    int xSize = this->currentResult->u1Size;
    double x = xMin;
    int ySize = this->currentResult->u2Size;

    for(int j = 0; j < xSize && !this->cancelled; ++j, x+=xStep){
        std::vector<TrajectoryResult>::iterator result_iterator = vector_iterator->begin();
        double y = yMin;
        for(int k = 0; k < ySize; ++k, y+=yStep){
            this->calculateTrajectoryResult(result_iterator, type, x, y, z, tests);

            ++result_iterator;
        }
        currentResult->addU1Column(&(*(vector_iterator)));
        ++vector_iterator;
    }

    CalculatedCut* result = this->currentResult;
    this->currentResult = NULL;

    return result;
}

class TBBCalculateCrossSection {
private:
    CrossSectionType type;
    double xMin;
    double xMax;
    double xStep;
    double yMin;
    double yMax;
    double yStep;
    double z;
    std::vector<TrajectoryTest>* tests;
    TrajectoryCalculator* calculator;
    tbb::atomic<PartiallyCalculatedCut*> currentResult;

public:
    void operator()(const tbb::blocked_range<size_t>& r) const {
        if(calculator->cancelled){
            return;
        }
        size_t idx = r.begin();

        std::vector<std::vector<TrajectoryResult>>::iterator vector_iterator = currentResult->begin() + idx;
        int ySize = this->currentResult->u2Size;
        for(idx = r.begin(); idx != r.end() && !calculator->cancelled; ++idx){
            double x = xMin + (idx * xStep);
            std::vector<TrajectoryResult>::iterator result_iterator = vector_iterator->begin();
            double y = yMin;
            for(int j = 0; j < ySize; ++j, y+=yStep){
                calculator->calculateTrajectoryResult(result_iterator, type, x, y, this->z, this->tests);

                ++result_iterator;
            }
            currentResult->addU1Column(&(*(vector_iterator)));
            ++vector_iterator;
        }
    }

    TBBCalculateCrossSection(CrossSectionType type, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, double z, std::vector<TrajectoryTest>* tests, TrajectoryCalculator* calculator, PartiallyCalculatedCut* currentResult):
        type(type),
        xMin(xMin),
        xMax(xMax),
        xStep(xStep),
        yMin(yMin),
        yMax(yMax),
        yStep(yStep),
        z(z),
        tests(tests),
        calculator(calculator),
        currentResult(currentResult)  {
    }
};

CalculatedCut* TrajectoryCalculator::parallelCalculateCrossSection(CrossSectionType type, double xMin, double xMax, double xStep,double yMin, double yMax, double yStep, double z, std::vector<TrajectoryTest>* tests){
    this->currentResult = new PartiallyCalculatedCut(type, z, xMin, xMax, xStep, yMin, yMax, yStep, tests);

    tbb::parallel_for(tbb::blocked_range<size_t>(0, this->currentResult->u1Size, this->cancelled), TBBCalculateCrossSection(type, xMin, xMax, xStep, yMin, yMax, yStep, z, tests, this, this->currentResult));

    CalculatedCut* result = this->currentResult;
    this->currentResult = NULL;

    return result;
}

inline double TrajectoryCalculator::fu1(double u1, double u2, double i) {
    return ((u2 - u1) / R - (m2 * u1 + 0.5 * (m1 - m0)*(this->abs(u1 - Bp) - this->abs(u1 + Bp)) + 0.5 * (m2 - m1)*(this->abs(u1 - B0) - this->abs(u1 + B0))) - I) / C1;
}

inline double TrajectoryCalculator::fu2(double u1, double u2, double i) {
    return ((u1 - u2) / R + i) / C2;
}

inline double TrajectoryCalculator::fi(double u2, double i) {
    return (-u2 - ro * i) / L;
}

inline double TrajectoryCalculator::abs(double n){
    if(n < 0){
       return -n;
    }
    return n;
}


bool TrajectoryCalculator::hasPartialResult(){
    return this->currentResult != NULL;
}

PartiallyCalculatedCut* TrajectoryCalculator::partialResult(){
    return this->currentResult;
}
