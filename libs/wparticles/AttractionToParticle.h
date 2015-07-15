#pragma once

#include "Force.h"
#include "Space.h"

class AttractionToParticle : public Force
{
public:
    AttractionToParticle(Space &space);
    wmath::Vector3Dd effect(const Particle &particle) const;

private:
    Space &m_space;
};
