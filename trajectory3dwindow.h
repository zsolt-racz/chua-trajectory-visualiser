#ifndef TRAJECTORY3DWINDOW_H
#define TRAJECTORY3DWINDOW_H

#include <QWidget>
#include <QString>
#include <QColor>
#include "trajectorytest.h"
#include "qplot3d/QPlot3D.h"

class Trajectory3DWindow : public QPlot3D
{
public:
    Trajectory3DWindow(QWidget* parent=NULL);
    void addTest(TrajectoryTest test);
};

#endif // TRAJECTORY3DWINDOW_H
