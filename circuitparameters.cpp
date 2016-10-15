#include "circuitparameters.h"

CircuitParameters::CircuitParameters(std::string fileName)
{
    this->loadFromFile(fileName);
}
CircuitParameters::CircuitParameters(double C1, double C2, double L, double Bp, double B0, double R, double ro, double I, double m0, double m1, double m2, double t_max,double h0, double iStepMax, double uStepMax) :
    C1(C1), C2(C2), L(L), Bp(Bp), B0(B0), R(R), ro(ro), I(I), m0(m0), m1(m1), m2(m2), t_max(t_max), h0(h0), iStepMax(iStepMax), uStepMax(uStepMax) {
}

void CircuitParameters::loadFromFile(std::string fileName){
    std::ifstream file;
    file.open(fileName.c_str());
    file >> this->C1 >> this->C2 >> this->L >> this->Bp >> this->B0 >> this->R >> this->ro >> this->I >> this->m0 >> this->m1 >> this->m2 >> this->t_max >> this->h0 >> this->iStepMax >> this->uStepMax;
    file.close();
}

void CircuitParameters::saveToFile(std::string fileName){
    std::ofstream output;
    output.open(fileName.c_str());

    output << std::fixed << std::setprecision(15) <<
            this->C1 << "\t" <<
            this->C2 << "\t" <<
            this->L << "\t" <<
            this->Bp << "\t" <<
            this->B0 << "\t" <<
            this->R << "\t" <<
            this->ro << "\t" <<
            this->I << "\t" <<
            this->m0 << "\t" <<
            this->m1 << "\t" <<
            this->m2 << "\t" <<
            this->t_max << "\t" <<
            this->h0  << "\t" <<
            this->iStepMax  << "\t" <<
            this->uStepMax;

    output.close();
}
