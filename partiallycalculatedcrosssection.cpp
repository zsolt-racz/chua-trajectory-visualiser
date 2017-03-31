#include "partiallycalculatedcrosssection.h"

PartiallyCalculatedCrossSection::PartiallyCalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests):
    CalculatedCrossSection(type, columnMin, columnMax, columnCount, rowMin, rowMax, rowCount, depth, tests){
    this->currentProgress = 0;
}


std::list<std::vector<TrajectoryResult>*>::const_iterator PartiallyCalculatedCrossSection::cbeginColumns(){
    return this->calculatedColumns.cbegin();
}

std::list<std::vector<TrajectoryResult>*>::const_iterator PartiallyCalculatedCrossSection::cendColumns(){
    return this->calculatedColumns.cend();
}

void PartiallyCalculatedCrossSection::addColumn(std::vector<TrajectoryResult>* column){
    this->calculatedColumns.push_back(column);
}

double PartiallyCalculatedCrossSection::progress(){
    return (double)this->calculatedColumns.size()/this->columnCount;
}
