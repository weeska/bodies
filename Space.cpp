#include "Space.h"

#include "Attraction.h"

Space::Space()
{
    this->addForce(std::make_shared<Attraction>(0.1, Math::Vector3D()));
    this->addForce(std::make_shared<Attraction>(0.01, Math::Vector3D(-0.2, 0.5)));
    this->addForce(std::make_shared<Attraction>(0.01, Math::Vector3D(-0.8, -0.3)));
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
        Math::Vector3D effect;

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

