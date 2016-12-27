#include "trajectoryresult.h"

TrajectoryResultType TrajectoryResult::result() const{
    if(this->test == NULL){
        return TrajectoryResultType::UNDETERMINED;
    }else{
        return this->test->type;
    }
}
