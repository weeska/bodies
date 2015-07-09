#pragma once

#include "Force.h"

class Attraction : public Force
{
public:
    Attraction(double strength, const Vector3D &position);

    Vector3D effect(const Particle &particle) const;

private:
    double m_strength;
    Vector3D m_target;
};
