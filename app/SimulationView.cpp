#include "SimulationView.h"

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

SimulationView::SimulationView(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_showVelocities(false)
    , m_particleGenerator(std::make_shared<UniformParticleGenerator>(4000))
{
    this->reset();

    QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(tick()));
    this->tick();
}

void SimulationView::tick()
{
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
    static const double scale = 1000.0;
    glOrtho(-scale, scale, -scale, scale, -1.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SimulationView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void SimulationView::drawMotionVectors()
{
    glBegin(GL_LINES);
    for(ParticlePtr particle : m_space.constParticles()) {
        static const double dt = 0.0001;
        const wmath::Vector3Dd &acceleration = particle->acceleration();
        const wmath::Vector3Dd &position = particle->position();
        const wmath::Vector3Dd &velocity = particle->constVelocity();

        auto p = [&](int i) { return position[i] + dt * velocity[i] + 0.5 * dt * dt * acceleration[i];};
        auto v = [&](int i) { return velocity[i] + dt * acceleration[i];};

        glColor4d(1.0, 1.0, 0.0, 0.2);
        glVertex3d(p(0), p(1), p(2));
        glColor4d(1.0, 0.0, 0.0, 0.2);
        glVertex3d(p(0) + v(0) * 0.001, p(1) + v(1) * 0.001, p(2) + v(2) * 0.001);
    }
    glEnd();
}

void SimulationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(m_showVelocities) {
        this->drawMotionVectors();
    }

    glBegin(GL_POINTS);
    for(ParticlePtr particle : m_space.constParticles()) {
        const wmath::Vector3Dd &color = particle->constColor();
        const wmath::Vector3Dd &position = particle->constPosition();
        glColor4d(color[0], color[1], color[2], 0.6);
        glVertex3dv(position.data());
    }
    glEnd();
}

