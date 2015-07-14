#pragma once

#include "Force.h"

class Attraction : public Force
{
public:
    Attraction(double strength, const wmath::Vector3D &position);

    wmath::Vector3D effect(const Particle &particle) const;

private:
    double m_strength;
    wmath::Vector3D m_target;
};
