#include "trajectorytest.h"

TrajectoryTest::TrajectoryTest(std::string name, TrajectoryResultType type, std::string color, double u1Lo, double u1Hi, double u2Lo, double u2Hi, double iLo, double iHi): name(name), type(type), color(color), u1Lo(u1Lo), u1Hi(u1Hi), u2Lo(u2Lo), u2Hi(u2Hi), iLo(iLo), iHi(iHi)
{

}

bool TrajectoryTest::eval(double u1, double u2, double i) const{
    if(this->type == CHA){
        return u1 < this->u1Hi && u1 > this->u1Lo && u2 < this->u2Hi && u2 > this->u2Lo && i < this->iHi && i > this->iLo;
    }else if(this->type == LC){
        return i > this->iHi || i < this->iLo || u1 > this->u1Hi || u1 < this->u1Lo || u2 > this->u2Hi || u2 < this->u2Lo;
    }

    throw 1;
}


bool TrajectoryTest::operator==(const TrajectoryTest& tt) const {
    return
        this->name == tt.name &&
        this->type == tt.type &&
        this->color == tt.color &&
        this->u1Lo == tt.u1Lo &&
        this->u1Hi == tt.u1Hi &&
        this->u2Lo == tt.u2Lo &&
        this->u2Hi == tt.u2Hi &&
        this->iLo == tt.iLo &&
        this->iHi == tt.iHi;
}
