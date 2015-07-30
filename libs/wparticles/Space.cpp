#include "Space.h"
#include <cassert>
#include <thread>
#include <future>
static const double dt = 0.0001;

void Space::applyEffects()
{
    for(ParticlePtr &particle : m_particles) {
        wmath::Vec3d &position = particle->position();
        wmath::Vec3d &velocity = particle->velocity();
        wmath::Vec3d &acceleration = particle->acceleration();

        for(int i=0; i < 3; ++i) {
            velocity[i] += dt * acceleration[i];
            position[i] += dt * velocity[i] + 0.5 * dt * dt * acceleration[i];
        }
        acceleration *= 0.0;
    }
}
void Space::setAccumulator(SpaceAccumulator *accumulator)
{
    m_accumulator.reset(accumulator);
}


void Space::tick()
{
    if(!m_accumulator) {
        return;
    }

    m_accumulator->accumulate(m_particles);
    this->applyEffects();
}

std::vector<ParticlePtr> &Space::particles()
{
    return m_particles;
}

const std::vector<ParticlePtr> &Space::constParticles() const
{
    return m_particles;
}

