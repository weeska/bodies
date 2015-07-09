#include "Space.h"

#include "Attraction.h"

Space::Space()
{
    this->addForce(std::make_shared<Attraction>(0.2, Vector3D()));
}

Space::~Space()
{

}

void Space::addForce(ForcePtr force)
{
    m_forces.push_back(force);
}

void Space::addParticle(ParticlePtr particle)
{
    m_particles.push_back(particle);
}

void Space::tick()
{
    for(ParticlePtr p : *this) {
        Vector3D effect;

        for(ForcePtr force : m_forces) {
            effect += force->effect(*p);
        }

        p->setPosition(p->position() + effect);
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

