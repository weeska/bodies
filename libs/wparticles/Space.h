#pragma once

#include <map>
#include <vector>

#include "Particle.h"

class Space
{
public:
    void tick();
    std::vector<ParticlePtr> &particles();
    const std::vector<ParticlePtr> &constParticles() const;

    void accumulateEffects(int from, int to);
private:
    void applyEffects();
private:
    std::vector<ParticlePtr> m_particles;
};
