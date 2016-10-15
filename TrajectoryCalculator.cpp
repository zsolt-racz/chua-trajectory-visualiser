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

    // Save initial coordinates at t=0
    points->push_back(new Point3DT(i0, u1_0, u2_0, 0));
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

            h = hdiv2;
            ++divisionCount;
        }else{
            i = i + iDiff;
            u1 = u1 + u1Diff;
            u2 = u2 + u2Diff;

            if(h != h0){
                h = h * 2;
            }

            points->push_back(new Point3DT(i, u1, u2, t));
        }
    }

    return new Trajectory(points, divisionCount);
}

TrajectoryResultType::ResultType TrajectoryCalculator::calculateTrajectoryResult(double i0, double u1_0, double u2_0) {
    double i = i0;
    double u1 = u1_0;
    double u2 = u2_0;

    double h = h0;

    for (double t = h; t <= t_max; t += h) {
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

            h = hdiv2;
        }else{
            i = i + iDiff;
            u1 = u1 + u1Diff;
            u2 = u2 + u2Diff;

            if(h != h0){
                h = h * 2;
            }

            if(t > 50){
                /* Test LC */
                if (i > 30 || i < -30) {
                    return TrajectoryResultType::LC;
                }

                /* Test CHA */
                if (u2 < -4.75 && u2 > -5.25 && u1 < 0.25 && u1 > -0.25 && i < 5 && i > -5) {
                    return TrajectoryResultType::CHA;
                }
            }
        }
    }

    return TrajectoryResultType::UNDETERMINED;

}

CalculatedCut* TrajectoryCalculator::calculateCut(double u1Min, double u1Max, double u1Step,double u2Min, double u2Max, double u2Step, double i){
    this->currentResult = new PartiallyCalculatedCut(i, u1Min, u1Max, u1Step, u2Min, u2Max, u2Step);

    std::vector<std::vector<CalculatedCut::TrajectoryResult>>::iterator vector_iterator = currentResult->begin();
    for(double u1 = u1Min; u1<=u1Max; u1+=u1Step){
        std::vector<CalculatedCut::TrajectoryResult>::iterator result_iterator = vector_iterator->begin();
        for(double u2 = u2Min; u2<=u2Max; u2+=u2Step){
            result_iterator->u1 = u1;
            result_iterator->u2 = u2;
            result_iterator->t = -1;
            result_iterator->result = this->calculateTrajectoryResult(i, u1, u2);
            ++result_iterator;
        }
        currentResult->addU1Column(vector_iterator.base());
        ++vector_iterator;
    }

    CalculatedCut* result = this->currentResult->createCalculatedCut();

    delete this->currentResult;
    this->currentResult = NULL;

    return result;
}

class TBBCalculateCut {
private:
    double u1Min;
    double u1Max;
    double u1Step;
    double u2Min;
    double u2Max;
    double u2Step;
    double i;
    TrajectoryCalculator* calculator;
    tbb::atomic<PartiallyCalculatedCut*> currentResult;

public:
    void operator()(const tbb::blocked_range<size_t>& r) const {
        size_t idx = r.begin();

        std::vector<std::vector<CalculatedCut::TrajectoryResult>>::iterator vector_iterator = currentResult->begin() + idx;
        for(idx = r.begin(); idx != r.end(); ++idx){
            double u1 = u1Min + (idx * u1Step);
            std::vector<CalculatedCut::TrajectoryResult>::iterator result_iterator = vector_iterator->begin();
            for(double u2 = u2Min; u2<=u2Max; u2+=this->u2Step){
                result_iterator->u1 = u1;
                result_iterator->u2 = u2;
                result_iterator->t = -1;
                result_iterator->result = this->calculator->calculateTrajectoryResult(this->i, u1, u2);
                ++result_iterator;
            }
            currentResult->addU1Column(vector_iterator.base());
            ++vector_iterator;
        }
    }

    TBBCalculateCut(double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step, double i, TrajectoryCalculator* calculator, PartiallyCalculatedCut* currentResult):
        u1Min(u1Min),
        u1Max(u1Max),
        u1Step(u1Step),
        u2Min(u2Min),
        u2Max(u2Max),
        u2Step(u2Step),
        i(i),
        calculator(calculator),
        currentResult(currentResult)  {
    }
};

CalculatedCut* TrajectoryCalculator::parallelCalculateCut(double u1Min, double u1Max, double u1Step,double u2Min, double u2Max, double u2Step, double i){
    this->currentResult = new PartiallyCalculatedCut(i, u1Min, u1Max, u1Step, u2Min, u2Max, u2Step);

    tbb::parallel_for(tbb::blocked_range<size_t>(0, this->currentResult->u1Size), TBBCalculateCut(u1Min, u1Max, u1Step, u2Min, u2Max, u2Step, i, this, this->currentResult));

    CalculatedCut* result = this->currentResult->createCalculatedCut();

    delete this->currentResult;
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
