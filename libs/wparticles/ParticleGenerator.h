#pragma once

#include "Space.h"

class ParticleGenerator {
public:
    virtual void generate(Space &data) const = 0;
};
