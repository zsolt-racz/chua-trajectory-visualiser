#include "circuitparameters.h"

CircuitParameters::CircuitParameters()
{

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
