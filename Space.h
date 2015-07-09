#pragma once

#include <vector>

#include "Particle.h"

class Space
{
public:
    using ParticleContainer = std::vector<ParticlePtr>;
    using ParticleIterator = ParticleContainer::iterator;

    Space();
    ~Space();

    void addParticle(ParticlePtr particle);

    void tick();

    ParticleIterator begin();
    ParticleIterator end();

private:
    ParticleContainer m_particles;
};
