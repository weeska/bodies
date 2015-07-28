#pragma once

#include <map>
#include <vector>

#include "Particle.h"
#include "SpaceAccumulator.h"

class Space
{
public:
    void tick();
    std::vector<ParticlePtr> &particles();
    const std::vector<ParticlePtr> &constParticles() const;

    void setAccumulator(SpaceAccumulator *accumulator);

private:
    void applyEffects();

private:
    std::unique_ptr<SpaceAccumulator> m_accumulator;
    std::vector<ParticlePtr> m_particles;
};
