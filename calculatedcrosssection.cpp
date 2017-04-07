#include "calculatedcrosssection.h"

CalculatedCrossSection::CalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests):
    type(type),
    depth(depth),
    columnMin(columnMin),
    columnMax(columnMax),
    columnCount(columnCount),
    rowMin(rowMin),
    rowMax(rowMax),
    rowCount(rowCount),
    tests(tests)
{
    this->results = std::vector<std::vector<TrajectoryResult>>(columnCount, std::vector<TrajectoryResult>(rowCount));
}

CalculatedCrossSection::CalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, double depth, std::vector<TrajectoryTest>* tests, std::vector<std::vector<TrajectoryResult>> results):
    type(type),
    depth(depth),
    columnMin(columnMin),
    columnMax(columnMax),
    columnCount(columnCount),
    rowMin(rowMin),
    rowMax(rowMax),
    rowCount(rowCount),
    tests(tests),
    results(results){}

CalculatedCrossSection::CalculatedCrossSection(CrossSectionType type, double columnMin, double columnMax, double columnCount, double rowMin, double rowMax, double rowCount, std::vector<TrajectoryTest>* tests, std::string filePath):
    type(type),
    columnMin(columnMin),
    columnMax(columnMax),
    columnCount(columnCount),
    rowMin(rowMin),
    rowMax(rowMax),
    rowCount(rowCount),
    tests(tests)
{
    std::ifstream file;
    file.open(filePath);

    if(!file.good()){
        return;
    }

    this->results = std::vector<std::vector<TrajectoryResult>>(columnCount, std::vector<TrajectoryResult>(rowCount));

    double depth;
    for (std::vector<std::vector<TrajectoryResult>>::iterator vector_iterator = this->begin(); vector_iterator != this->end(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::iterator result_iterator = vector_iterator->begin(); result_iterator != vector_iterator->end(); ++result_iterator) {
            double x, y, z, t, result, testIdx, divisionCount;
            file >> std::setprecision(15) >> x >> y >> z >> result >> testIdx >> t >> divisionCount;

            if(this->type == I_U1){
                result_iterator->column = y;
                result_iterator->row = z;
                depth = x;
            }else if(this->type == I_U2){
                result_iterator->column = x;
                result_iterator->row = z;
                depth = y;
            }else if(this->type == U2_U1){
                result_iterator->column = y;
                result_iterator->row = x;
                depth = z;
            }

            result_iterator->t = t;
            result_iterator->divisionCount = divisionCount;

            if(testIdx >0 && testIdx <= this->tests->size()){
                result_iterator->test = &this->tests->at(testIdx-1);
            }
        }
    }

    file.close();
    this->depth = depth;
}

CalculatedCrossSection::~CalculatedCrossSection(){
    //delete this->tests;
}

void CalculatedCrossSection::writeToTxt(std::string filename, std::string separator, bool append, bool undeterminedOnly) {
    std::ofstream output;

    if(append){
        output.open(filename.c_str(), std::ios_base::app | std::ios_base::out);
    }else{
        output.open(filename.c_str());
    }

    for (std::vector<std::vector<TrajectoryResult>>::const_iterator vector_iterator = this->cbegin(); vector_iterator != this->cend(); ++vector_iterator) {
        for (std::vector<TrajectoryResult>::const_iterator result_iterator = vector_iterator->cbegin(); result_iterator != vector_iterator->cend(); ++result_iterator) {
            if(undeterminedOnly && result_iterator->result() != TrajectoryResultType::UNDETERMINED){
                continue;
            }
            int testId = this->getTestIndex(result_iterator->test);
            double x, y, z;
            if(this->type == I_U1){
                x = this->depth;
                y = result_iterator->column;
                z = result_iterator->row;
            }else if(this->type == I_U2){
                x = result_iterator->column;
                y = this->depth;
                z = result_iterator->row;
            }else if(this->type == U2_U1){
                x = result_iterator->row;
                y = result_iterator->column;
                z = this->depth;
            }

            output << std::setprecision(15) << x << separator << y << separator << z << separator << result_iterator->result() << separator << testId << separator << result_iterator->t << separator << result_iterator->divisionCount << "\n";
        }
    }

    output.close();
}




std::vector<std::vector<TrajectoryResult>>::iterator CalculatedCrossSection::begin(){
    return this->results.begin();
}

std::vector<std::vector<TrajectoryResult>>::iterator CalculatedCrossSection::end(){
    return this->results.end();
}

std::vector<std::vector<TrajectoryResult>>::const_iterator CalculatedCrossSection::cbegin(){
    return this->results.cbegin();
}

std::vector<std::vector<TrajectoryResult>>::const_iterator CalculatedCrossSection::cend(){
    return this->results.cend();
}

/** index starts at 1 **/
int CalculatedCrossSection::getTestIndex(const TrajectoryTest test){
    for(int i = 0; i < this->tests->size(); i++){
        if(this->tests->at(i) == test){
            return i + 1;
        }
    }

    return 0;
}

int CalculatedCrossSection::getTestIndex(const TrajectoryTest* test){
    if(test == NULL){
        return 0;
    }else{
        return this->getTestIndex(*test);
    }
}
