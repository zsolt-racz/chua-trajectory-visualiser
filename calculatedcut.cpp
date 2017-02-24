#include "calculatedcut.h"

CalculatedCut::CalculatedCut(CrossSectionType type, double z, double xMin, double xMax, double xSize, double yMin, double yMax, double ySize, std::vector<TrajectoryTest>* tests):
    type(type),
    z(z),
    xMin(xMin),
    xMax(xMax),
    xSize(xSize),
    yMin(yMin),
    yMax(yMax),
    ySize(ySize),
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

CalculatedCut::CalculatedCut(std::string filePath, std::vector<TrajectoryTest>* tests): tests(tests){
    std::ifstream file;
    file.open(filePath);

    if(!file.good()){
        return;
    }

    int type;
    file >> type;
    this->type = static_cast<CrossSectionType>(type);
    file >> std::setprecision(15) >> this->xMin >> this->xMax >> this->xSize >> this->yMin >> this->yMax >> this->ySize;

    this->results = std::vector<std::vector<TrajectoryResult>>(xSize, std::vector<TrajectoryResult>(ySize));

    for (std::vector<std::vector<TrajectoryResult>>::iterator vector_iterator = this->begin(); vector_iterator != this->end(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::iterator result_iterator = vector_iterator->begin(); result_iterator != vector_iterator->end(); ++result_iterator) {
            double x, y, z, t, result, testIdx, divisionCount;

            this->z = z;

            if(this->type == I_U1){
                file >> std::setprecision(15) >> y >> z >> x >> result >> testIdx >> t >> divisionCount;
            }else if(this->type == I_U2){
                file >> std::setprecision(15) >> y >> x >> z >> result >> testIdx >> t >> divisionCount;
            }else if(this->type == U2_U1){
                file >> std::setprecision(15) >> z >> y >> x >> result >> testIdx >> t >> divisionCount;
            }

            result_iterator->x = x;
            result_iterator->y = y;
            result_iterator->t = t;
            result_iterator->divisionCount = divisionCount;

            if(testIdx >0 && testIdx <= this->tests->size()){
                result_iterator->test = &this->tests->at(testIdx-1);
            }
        }
    }

    file.close();
}

CalculatedCut::~CalculatedCut(){
    //delete this->tests;
}

void CalculatedCut::writeToTxt(std::string filename, std::string separator) {
    std::ofstream output;
    output.open(filename.c_str());

    output << this->type  << separator;
    output << std::setprecision(15) << this->xMin << separator << this->xMax << separator << this->xSize << separator << this->yMin << separator << this->yMax << separator << this->ySize << "\n\n";

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = this->cbegin(); vector_iterator != this->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            int testId = this->getTestIndex(result_iterator->test);

            if(this->type == I_U1){
                output << std::setprecision(15) << result_iterator->y << separator << this->z << separator << result_iterator->x << separator << result_iterator->result() << separator << testId << separator << result_iterator->t << separator << result_iterator->divisionCount << "\n";
            }else if(this->type == I_U2){
                output << std::setprecision(15) << result_iterator->y << separator << result_iterator->x << separator << this->z << separator << result_iterator->result() << separator << testId << separator << result_iterator->t << separator << result_iterator->divisionCount << "\n";
            }else if(this->type == U2_U1){
                output << std::setprecision(15) << this->z << separator << result_iterator->y << separator << result_iterator->x << separator << result_iterator->result() << separator << testId << separator << result_iterator->t << separator << result_iterator->divisionCount << "\n";
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
