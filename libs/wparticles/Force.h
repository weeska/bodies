#pragma once

#include "Particle.h"

#include <memory>

class Particle;

class Force
{
public:
    virtual wmath::Vector3Dd effect(const Particle &particle) const = 0;
};

typedef std::shared_ptr<Force> ForcePtr;
