#pragma once

#include <memory>
#include <utility>

#include "wmath/Vector.h"

class Particle
{
public:
    using Position = wmath::Vector3Dd;

    Particle(double mass, double x, double y, double z);

    const Position &constPosition() const;
    void setPosition(const Position &constPosition);

    double mass() const;
    void setMass(double mass);

    const wmath::Vector3Dd &constVelocity() const;
    void setVelocity(const wmath::Vector3Dd &constVelocity);

private:
    double m_mass;
    Position m_position;
    wmath::Vector3Dd m_velocity;
};

typedef std::shared_ptr<Particle> ParticlePtr;
