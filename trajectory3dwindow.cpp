#include "trajectory3dwindow.h"

Trajectory3DWindow::Trajectory3DWindow(QWidget* parent): QPlot3D(parent)
{

}


void Trajectory3DWindow::addTest(TrajectoryTest test){
    QCurve3D* cube = new QCurve3D(QString::fromStdString(test.name));

    cube->addData(test.iHi,test.u2Hi,test.u1Hi);
    cube->addData(test.iHi,test.u2Lo,test.u1Hi);
    cube->addData(test.iHi,test.u2Lo,test.u1Lo);
    cube->addData(test.iHi,test.u2Hi,test.u1Lo);
    cube->addData(test.iHi,test.u2Hi,test.u1Hi);
    cube->addData(test.iLo,test.u2Hi,test.u1Hi);
    cube->addData(test.iLo,test.u2Lo,test.u1Hi);
    cube->addData(test.iLo,test.u2Lo,test.u1Hi);
    cube->addData(test.iLo,test.u2Lo,test.u1Lo);
    cube->addData(test.iLo,test.u2Hi,test.u1Lo);
    cube->addData(test.iLo,test.u2Hi,test.u1Hi);
    cube->addData(test.iLo,test.u2Lo,test.u1Hi);
    cube->addData(test.iHi,test.u2Lo,test.u1Hi);
    cube->addData(test.iHi,test.u2Lo,test.u1Lo);
    cube->addData(test.iLo,test.u2Lo,test.u1Lo);
    cube->addData(test.iLo,test.u2Hi,test.u1Lo);
    cube->addData(test.iHi,test.u2Hi,test.u1Lo);

    cube->setColor(QColor(QString::fromStdString(test.color)));
    cube->setLineWidth(3);


    this->addCurve(cube);
}
