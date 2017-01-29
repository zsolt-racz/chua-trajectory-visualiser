#include "calculatedcut.h"

CalculatedCut::CalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xStep, double yMin, double yMax, double yStep, std::vector<TrajectoryTest>* tests):
    type(type),
    z(z),
    xMin(xMin),
    xMax(xMax),
    xSize((int) std::floor(std::abs(xMax - xMin) / xStep) + 1),
    yMin(yMin),
    yMax(yMax),
    ySize((int) std::floor(std::abs(yMax - yMin) / yStep) + 1),
    tests(tests){
    this->results = std::vector<std::vector<TrajectoryResult>>(xSize, std::vector<TrajectoryResult>(ySize));
}

CalculatedCut::CalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xSize, double yMin, double yMax, double ySize, std::vector<TrajectoryTest>* tests, std::vector<std::vector<TrajectoryResult>> results):
    type(type),
    z(z),
    xMin(xMin),
    xMax(xMax),
    xSize(xSize),
    yMin(yMin),
    yMax(yMax),
    ySize(ySize),
    tests(tests),
    results(results){}

CalculatedCut::~CalculatedCut(){
    delete this->tests;
}

void CalculatedCut::writeToTxt(std::string filename) {
    std::ofstream output;
    output.open(filename.c_str());

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = this->cbegin(); vector_iterator != this->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            if(this->type == I_U1){
                output << std::setprecision(15) << result_iterator->y << "\t" << this->z << "\t" << result_iterator->x << "\t" << result_iterator->result() << "\t" << result_iterator->t << "\t" << result_iterator->divisionCount << "\n";
            }else if(this->type == I_U2){
                output << std::setprecision(15) << result_iterator->y << "\t" << result_iterator->x << "\t" << this->z << "\t" << result_iterator->result() << "\t" << result_iterator->t << "\t" << result_iterator->divisionCount << "\n";
            }else if(this->type == U2_U1){
                output << std::setprecision(15) << this->z << "\t" << result_iterator->y << "\t" << result_iterator->x << "\t" << result_iterator->result() << "\t" << result_iterator->t << "\t" << result_iterator->divisionCount << "\n";
            }
        }
    }

    output.close();
}


std::vector<std::vector<TrajectoryResult>>::iterator CalculatedCut::begin(){
    return this->results.begin();
}

std::vector<std::vector<TrajectoryResult>>::iterator CalculatedCut::end(){
    return this->results.end();
}

std::vector<std::vector<TrajectoryResult>>::const_iterator CalculatedCut::cbegin(){
    return this->results.cbegin();
}

std::vector<std::vector<TrajectoryResult>>::const_iterator CalculatedCut::cend(){
    return this->results.cend();
}

/** index starts at 1 **/
int CalculatedCut::getTestIndex(const TrajectoryTest test){
    for(int i = 0; i < this->tests->size(); i++){
        if(this->tests->at(i) == test){
            return i + 1;
        }
    }

    return 0;
}

int CalculatedCut::getTestIndex(const TrajectoryTest* test){
    if(test == NULL){
        return 0;
    }else{
        return this->getTestIndex(*test);
    }
}
