#include "SimulationView.h"

#include <random>

SimulationView::SimulationView()
{
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_real_distribution<double> dist;

    for(int i = 0; i < 2; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        double z = 0.0;

        x = x * 2.0 - 1.0;
        y = y * 2.0 - 1.0;

        m_space.addParticle(std::make_shared<Particle>(0.1, x, y, z));
    }

    QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(tick()));

    this->tick();
}

void SimulationView::tick()
{
    m_space.tick();
    m_timer.start(1);
    this->update();
}

void SimulationView::initializeGL()
{
    static const double scale = 100.0;
    glOrtho(-scale, scale, -scale, scale, -1.0, 1.0);
}

void SimulationView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void SimulationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(20.0);
    glBegin(GL_POINTS);
    for(ParticlePtr particle : m_space) {
        const Particle::Position &position = particle->position();
        glVertex3d(position.x(), position.y(), position.z());
    }
    glEnd();
}

