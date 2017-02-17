#include "partiallycalculatedcut.h"

PartiallyCalculatedCut::PartiallyCalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xSize, double yMin, double yMax, double ySize, std::vector<TrajectoryTest>* tests):
    CalculatedCut(type, z, xMin, xMax, xSize, yMin, yMax, ySize, tests){
    this->currentProgress = 0;
}


std::list<std::vector<TrajectoryResult>*>::const_iterator PartiallyCalculatedCut::cbeginXColumns(){
    return this->calculatedXColumns.cbegin();
}

std::list<std::vector<TrajectoryResult>*>::const_iterator PartiallyCalculatedCut::cendXColumns(){
    return this->calculatedXColumns.cend();
}

std::size_t PartiallyCalculatedCut::XCount(){
    return this->calculatedXColumns.size();
}

void PartiallyCalculatedCut::addXColumn(std::vector<TrajectoryResult>* x){
    this->calculatedXColumns.push_back(x);
}

double PartiallyCalculatedCut::progress(){
    return (double)this->XCount()/this->xSize;
}
