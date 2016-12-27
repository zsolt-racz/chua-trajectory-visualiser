#include "partiallycalculatedcut.h"

PartiallyCalculatedCut::PartiallyCalculatedCut(CrossSectionType type, double i, double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step, std::vector<TrajectoryTest>* tests):
    CalculatedCut(type, i, u1Min, u1Max, u1Step, u2Min, u2Max, u2Step, tests){
    this->currentProgress = 0;
}


std::list<std::vector<TrajectoryResult>*>::const_iterator PartiallyCalculatedCut::cbeginU1Columns(){
    return this->calculatedU1Columns.cbegin();
}

std::list<std::vector<TrajectoryResult>*>::const_iterator PartiallyCalculatedCut::cendU1Columns(){
    return this->calculatedU1Columns.cend();
}

std::size_t PartiallyCalculatedCut::U1Count(){
    return this->calculatedU1Columns.size();
}

void PartiallyCalculatedCut::addU1Column(std::vector<TrajectoryResult>* u1){
    this->calculatedU1Columns.push_back(u1);
}

double PartiallyCalculatedCut::progress(){
    return (double)this->U1Count()/this->u1Size;
}
