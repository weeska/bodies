#pragma once

#include "Force.h"

class Attraction : public Force
{
public:
    Attraction(double strength, const Math::Vector3D &position);

    Math::Vector3D effect(const Particle &particle) const;

private:
    double m_strength;
    Math::Vector3D m_target;
};
