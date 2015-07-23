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

private:
    void applyEffects();
private:
    std::vector<ParticlePtr> m_particles;
};
