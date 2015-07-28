#pragma once

#include "Particle.h"

class SpaceAccumulator {
public:
    void accumulate(std::vector<ParticlePtr> &particles);
    virtual void doAccumulateEffects(std::vector<ParticlePtr> &particles, int from, int to) = 0;
};
