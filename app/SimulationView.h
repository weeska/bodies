#pragma once

#include <QOpenGLWidget>
#include <QTimer>
#include "wparticles/Space.h"
#include "wparticles/UniformParticleGenerator.h"
#include "wparticles/Octree.h"

class SimulationView : public QOpenGLWidget
{
    Q_OBJECT

    Space m_space;
    std::shared_ptr<Octree> m_tree;
    QTimer m_timer;
    bool m_showOctree;
    bool m_useOctree;
    bool m_showVelocities;
    std::shared_ptr<ParticleGenerator> m_particleGenerator;
public:
    SimulationView(QWidget *parent);

    bool showOctree() const;
    bool showVelocities() const;
    bool useOctree() const;

public slots:
    void reset();
    void tick();
    void setShowOctree(bool showOctree);
    void setShowVelocities(bool show);
    void setUseOctree(bool useOctree);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void buildOctree();
    void drawMotionVectors();
    void drawOctree();
    void drawOctreeCell(const wmath::Vec3d &center, const double halfEdgeLength) const;
};
