#ifndef CROSSSECTIONMAP_H
#define CROSSSECTIONMAP_H

#include <map>
#include <vector>
#include "trajectorytest.h"
#include "qcustomplot/qcustomplot.h"


class CrossSectionMap : public QCPColorMap
{
public:
    CrossSectionMap(QCPAxis *keyAxis, QCPAxis *valueAxis);
    void updateMapImage();
    void colorize(const double *data, const QCPRange &range, QRgb *scanLine, int n, int dataIndexFactor, bool logarithmic);
    void updateColors(std::vector<TrajectoryTest>* tests);
private:
    std::map<int, std::string> colors;
};

#endif // CROSSSECTIONMAP_H
