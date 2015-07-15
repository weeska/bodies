#pragma once

#include "Force.h"

class Attraction : public Force
{
public:
    Attraction(double strength, const wmath::Vector3Dd &position);

    wmath::Vector3Dd effect(const Particle &particle) const;

private:
    double m_strength;
    wmath::Vector3Dd m_target;
};
