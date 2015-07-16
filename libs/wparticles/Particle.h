#pragma once

#include <memory>
#include <utility>

#include "wmath/Vector.h"

class Particle
{
public:
    Particle(double mass, double x, double y, double z);

    const wmath::Vector3Dd &constPosition() const;
    const wmath::Vector3Dd &constVelocity() const;

    double mass() const;
    wmath::Vector3Dd &acceleration();
    wmath::Vector3Dd &position();
    wmath::Vector3Dd &velocity();

    void setMass(double mass);
    void setAcceleration(const wmath::Vector3Dd &acceleration);
    void setPosition(const wmath::Vector3Dd &position);
    void setVelocity(const wmath::Vector3Dd &constVelocity);

private:
    double m_mass;
    wmath::Vector3Dd m_acceleration;
    wmath::Vector3Dd m_position;
    wmath::Vector3Dd m_velocity;
};

typedef std::shared_ptr<Particle> ParticlePtr;
