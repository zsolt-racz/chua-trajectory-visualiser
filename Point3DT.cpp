#include "Point3DT.h"

Point3DT::Point3DT(double i, double u1, double u2, double t) : i(i), u1(u1), u2(u2), t(t) {

}

double Point3DT::getI() const {
    return this->i;
}

double Point3DT::getU1() const {
    return this->u1;
}

double Point3DT::getU2() const {
    return this->u2;
}

double Point3DT::getT() const {
    return this->t;
}

