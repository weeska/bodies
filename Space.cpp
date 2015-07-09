#include "Space.h"

Space::Space()
{

}

Space::~Space()
{

}

void Space::addParticle(ParticlePtr particle)
{
    m_particles.push_back(particle);
}

void Space::tick()
{
    for(ParticlePtr p : *this) {
        const Particle::Position &pos = p->position();
        p->setPosition(Particle::Position(pos.first * 0.99, pos.second * 0.99));
    }
}

Space::ParticleIterator Space::begin()
{
    return m_particles.begin();
}

Space::ParticleIterator Space::end()
{
    return m_particles.end();
}

