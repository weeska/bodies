#pragma once

#include <QOpenGLWidget>
#include <QTimer>

#include <memory>

#include "wparticles/Space.h"
#include "wparticles/UniformParticleGenerator.h"

class SimulationView : public QOpenGLWidget
{
    Q_OBJECT

    Space m_space;
    QTimer m_timer;
    bool m_showVelocities;
    std::shared_ptr<ParticleGenerator> m_particleGenerator;
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
