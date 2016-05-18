#ifndef POINT3DT_H
#define POINT3DT_H

struct Point3DT {
public:
    const double i;
    const double u1;
    const double u2;
    const double t;

    Point3DT(double i, double u1, double u2, double t);

    double getI() const;
    double getU1() const;
    double getU2() const;
    double getT() const;

};

#endif /* POINT3DT_H */

