#include "SimulationView.h"

#include <QQueue>
#include <cassert>
#include <cmath>
#include <random>

static const double PI = 4 * std::atan(1);


bool SimulationView::showVelocities() const
{
    return m_showVelocities;
}

void SimulationView::reset()
{
    if(m_particleGenerator) {
        m_particleGenerator->generate(m_space.particles());
    }
}


bool SimulationView::showOctree() const
{
    return m_showOctree;
}

void SimulationView::setShowOctree(bool showOctree)
{
    m_showOctree = showOctree;
}

bool SimulationView::useOctree() const
{
    return m_useOctree;
}

void SimulationView::setUseOctree(bool useOctree)
{
    m_useOctree = useOctree;
}
SimulationView::SimulationView(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_tree(std::make_shared<Octree>(wmath::Vec3d(0.0, 0.0, 0.0), 1000.0))
    , m_showOctree(false)
    , m_useOctree(false)
    , m_showVelocities(false)
    , m_particleGenerator(std::make_shared<UniformParticleGenerator>(4000))
{
    this->reset();

    QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(tick()));
    this->tick();
}

void SimulationView::tick()
{
    if(m_showOctree || m_useOctree) {
        this->buildOctree();
    }
    m_space.tick();

    this->update();
    m_timer.start(1);
}

void SimulationView::setShowVelocities(bool show)
{
    if(m_showVelocities != show) {
        m_showVelocities = show;
        this->update();
    }
}

void SimulationView::initializeGL()
{
    static const double scale = 1100.0;
    const double ratio = static_cast<double>(this->width())/this->height();
    glOrtho(-scale*ratio, scale*ratio, -scale, scale, -scale, scale);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SimulationView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    static const double scale = 1100.0;
    const double ratio = static_cast<double>(w)/h;
    glLoadIdentity();
    glOrtho(-scale*ratio, scale*ratio, -scale, scale, -scale, scale);
}

void SimulationView::drawMotionVectors()
{
    glBegin(GL_LINES);
    for(ParticlePtr particle : m_space.constParticles()) {
        static const double dt = 0.0001;
        const wmath::Vec3d &acceleration = particle->acceleration();
        const wmath::Vec3d &position = particle->position();
        const wmath::Vec3d &velocity = particle->constVelocity();

        auto p = [&](int i) { return position[i] + dt * velocity[i] + 0.5 * dt * dt * acceleration[i];};
        auto v = [&](int i) { return velocity[i] + dt * acceleration[i];};

        glColor4d(1.0, 1.0, 0.0, 0.2);
        glVertex3d(p(0), p(1), p(2));
        glColor4d(1.0, 0.0, 0.0, 0.2);
        glVertex3d(p(0) + v(0) * 0.001, p(1) + v(1) * 0.001, p(2) + v(2) * 0.001);
    }
    glEnd();
}

void SimulationView::drawOctreeCell(const wmath::Vec3d &center, const double halfEdgeLength) const
{
    glPushMatrix();
        glTranslated(center[0], center[1], center[2]);
        glScaled(halfEdgeLength, halfEdgeLength, halfEdgeLength);

        glBegin(GL_LINES);

            //TOP
            glVertex3d(1.0, 1.0, 1.0);
            glVertex3d(1.0, 1.0, -1.0);

            glVertex3d(1.0, 1.0, -1.0);
            glVertex3d(-1.0, 1.0, -1.0);

            glVertex3d(-1.0, 1.0, -1.0);
            glVertex3d(-1.0, 1.0, 1.0);

            //Front
            glVertex3d(1.0, 1.0, 1.0);
            glVertex3d(1.0, -1.0, 1.0);

            glVertex3d(1.0, -1.0, 1.0);
            glVertex3d(-1.0, -1.0, 1.0);

            glVertex3d(-1.0, -1.0, 1.0);
            glVertex3d(-1.0, 1.0, 1.0);

        glEnd();
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
}

void SimulationView::buildOctree()
{
    m_tree->reset();
    for(ParticlePtr particle : m_space.constParticles()) {
        m_tree->insert(particle);
    }

    if(m_useOctree) {
        m_tree->computeMeans();
    }
}

void SimulationView::drawOctree()
{
    glColor4d(1.0, 1.0, 1.0, 0.1);
    glEnable(GL_DEPTH_TEST);

    QQueue<std::shared_ptr<Octree> > trees;
    trees << m_tree;

    while(!trees.empty()) {
        const std::shared_ptr<Octree> tree = trees.front();
        if(!tree) {
            break;
        }

        const wmath::Vec3d &center = tree->center();
        const double halfEdgeLength = tree->halfEdgeLength();

        this->drawOctreeCell(center, halfEdgeLength);

        if(!tree->isLeaf()) {
            for(auto t : tree->children()) {
                trees << t;
            }
        }
        trees.pop_front();
    }
}

void SimulationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotated(45, 1.0, 0.0, 0.0);
        glRotated(45, 0.0, 1.0, 0.0);

        if(m_showVelocities) {
            this->drawMotionVectors();
        }

        if(m_showOctree) {
            this->drawOctree();
        }

        glBegin(GL_POINTS);
        for(ParticlePtr particle : m_space.constParticles()) {
            const wmath::Vec3d &color = particle->constColor();
            const wmath::Vec3d &position = particle->constPosition();
            glColor4d(color[0], color[1], color[2], 0.6);
            glVertex3dv(position.data());
        }

    glEnd();

    glPopMatrix();
}

