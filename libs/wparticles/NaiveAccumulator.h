#pragma once

#include "SpaceAccumulator.h"

class NaiveAccumulator : public SpaceAccumulator
{
public:
    void doAccumulateEffects(std::vector<ParticlePtr> &particles, int from, int to);
};
