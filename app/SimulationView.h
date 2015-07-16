#pragma once

#include <QOpenGLWidget>
#include <QTimer>
#include "wparticles/Space.h"

class SimulationView : public QOpenGLWidget
{
    Q_OBJECT

    Space m_space;
    QTimer m_timer;
public:
    SimulationView();

    void drawMotionVectors();
public slots:
    void tick();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};
