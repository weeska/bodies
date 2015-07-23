#pragma once

#include "Particle.h"

class ParticleGenerator {
public:
    virtual void generate(std::vector<ParticlePtr> &particles) const = 0;
};
