#pragma once

#include <vector>

#include "Force.h"
#include "Particle.h"

class Space
{
public:
    using ForceContainer = std::vector<ForcePtr>;
    using ParticleContainer = std::vector<ParticlePtr>;
    using ParticleIterator = ParticleContainer::iterator;

    Space();

    void addForce(ForcePtr force);
    void addParticle(ParticlePtr particle);

    void tick();

    ParticleIterator begin();
    ParticleIterator end();

private:
    ForceContainer m_forces;
    ParticleContainer m_particles;
};
