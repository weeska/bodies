#pragma once

#include <map>
#include <vector>

#include "Particle.h"

class Space
{
public:
    using ParticleContainer = std::vector<ParticlePtr>;
    using ParticleIterator = ParticleContainer::iterator;

    Space();

    void addParticle(ParticlePtr particle);

    void tick();


    ParticleIterator begin();
    ParticleIterator end();
    void accumulateEffects();
    void applyEffects();
private:
    ParticleContainer m_particles;
};
