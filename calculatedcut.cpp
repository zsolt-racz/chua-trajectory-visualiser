#include "calculatedcut.h"

CalculatedCut::CalculatedCut(CrossSectionType type, double i, double u1Min, double u1Max, double u1Step, double u2Min, double u2Max, double u2Step, std::vector<TrajectoryTest>* tests):
    type(type),
    i(i),
    u1Min(u1Min),
    u1Max(u1Max),
    u1Size((int) std::floor(std::abs(u1Max - u1Min) / u1Step) + 1),
    u2Min(u2Min),
    u2Max(u2Max),
    u2Size((int) std::floor(std::abs(u2Max - u2Min) / u2Step) + 1),
    tests(tests){
    this->results = std::vector<std::vector<TrajectoryResult>>(u1Size, std::vector<TrajectoryResult>(u2Size));
}

CalculatedCut::CalculatedCut(CrossSectionType type, double i, double u1Min, double u1Max, double u1Size, double u2Min, double u2Max, double u2Size, std::vector<TrajectoryTest>* tests, std::vector<std::vector<TrajectoryResult>> results):
    type(type),
    i(i),
    u1Min(u1Min),
    u1Max(u1Max),
    u1Size(u1Size),
    u2Min(u2Min),
    u2Max(u2Max),
    u2Size(u2Size),
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
            output << std::setprecision(15) << this->i << "\t" << result_iterator->x << "\t" << result_iterator->y << "\t" << result_iterator->result() << "\t" << result_iterator->t << "\t" << result_iterator->divisionCount << "\n";
        }
    }

    output.close();
}

void CalculatedCut::writeToPLY(std::string filename) {
    std::ofstream output;
    output.open(filename.c_str());

    output << "ply" << "\n";
    output << "format ascii 1.0" << "\n";
    output << "element vertex " << this->results.size() << "\n";
    output << "property float x" << "\n";
    output << "property float y" << "\n";
    output << "property float z" << "\n";
    output << "end_header" << "\n";

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = this->cbegin(); vector_iterator != this->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            if(result_iterator->result() == TrajectoryResultType::CHA){
                output << this->i << " " << result_iterator->x << " " << result_iterator->y << "\n";
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
