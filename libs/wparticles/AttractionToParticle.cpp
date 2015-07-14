#include "AttractionToParticle.h"

#include <cmath>

AttractionToParticle::AttractionToParticle(Space &space)
    : m_space(space)
{
}

wmath::Vector3D AttractionToParticle::effect(const Particle &particle) const
{
    wmath::Vector3D result;

    for(ParticlePtr target : m_space) {

        if(target.get() == &particle) {
            continue;
        }

        const wmath::Vector3D difference = (particle.position() - target->position());

        const double invr3 = std::pow(1.0/difference.length(), 3.0);
        const double f = particle.mass() * invr3;

        result += difference * f;
    }

    return result;
}

