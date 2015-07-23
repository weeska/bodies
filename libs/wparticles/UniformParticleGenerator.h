#pragma once

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
    size_t m_particleCount;
    uint_fast32_t m_seed;

public:
    UniformParticleGenerator(size_t count = 1000, uint_fast32_t seed = 1);
    void setSeed(uint_fast32_t seed);
    void setParticleCount(size_t particleCount);

    virtual void generate(Space &space) const;
};
