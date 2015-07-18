#pragma once

#include <QOpenGLWidget>
#include <QTimer>
#include "wparticles/Space.h"

class SimulationView : public QOpenGLWidget
{
    Q_OBJECT

    Space m_space;
    QTimer m_timer;
    bool m_showVelocities;
public:
    SimulationView(QWidget *parent);

    void drawMotionVectors();
    bool showVelocities() const;

public slots:
    void reset();
    void tick();
    void setShowVelocities(bool show);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};
