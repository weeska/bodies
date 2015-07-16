#include "SimulationView.h"

#include <cassert>
#include <random>

SimulationView::SimulationView()
{
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_real_distribution<double> dist;

    //ParticlePtr p = std::make_shared<Particle>(10e30, 0.0, 0.0, 0.0);
    //m_space.addParticle(p);

    const int N = 1000;
    for(int i = 0; i < N; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        double z = 0.0;

        x = x * N * 1.0 - N * 0.5;
        y = y * N * 1.0 - N * 0.5;

        ParticlePtr p = std::make_shared<Particle>(100, x, y, z);
        m_space.addParticle(p);
    }

    QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(tick()));

    this->tick();
}

void SimulationView::tick()
{
    m_space.accumulateEffects();
    this->update();
    m_space.applyEffects();
    this->update();
    m_timer.start(1);
}

void SimulationView::initializeGL()
{
    static const double scale = 1000.0;
    glOrtho(-scale, scale, -scale, scale, -1.0, 1.0);
    glPointSize(2.0);
}

void SimulationView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void SimulationView::drawMotionVectors()
{
    glBegin(GL_LINES);
    glColor3d(1.0, 1.0, 0.0);
    for(ParticlePtr particle : m_space) {
        static const double dt = 1.0;
        const wmath::Vector3Dd &position = particle->position();
        const wmath::Vector3Dd &acceleration = particle->acceleration();
        const wmath::Vector3Dd &velocity = particle->constVelocity();

        auto p = [&](int i) { return position[i] + dt * velocity[i] + 0.5 * dt * dt * acceleration[i];};
        auto v = [&](int i) { return velocity[i] + dt * acceleration[i];};

        glVertex3d(p(0), p(1), p(2));
        glVertex3d(p(0) + v(0), p(1) + v(1), p(2) + v(2));
    }
    glEnd();
}

void SimulationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for(ParticlePtr particle : m_space) {
        const wmath::Vector3Dd &position = particle->constPosition();
        glVertex3dv(position.data());
    }
    glEnd();

    //drawMotionVectors();
}

