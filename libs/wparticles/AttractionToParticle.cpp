#include "AttractionToParticle.h"

#include <cmath>

AttractionToParticle::AttractionToParticle(Space &space)
    : m_space(space)
{
}

wmath::Vector3Dd AttractionToParticle::effect(const Particle &particle) const
{
    wmath::Vector3Dd result;

    for(ParticlePtr target : m_space) {

        if(target.get() == &particle) {
            continue;
        }

        const wmath::Vector3Dd &difference = (particle.constPosition() - target->constPosition());

        const double invr3 = std::pow(1.0/difference.length(), 3.0);
        const double f = particle.mass() * invr3;

        result += difference * f;
    }

    return std::move(result);
}

