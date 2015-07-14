#pragma once

#include <memory>
#include <utility>

#include "wmath/Vector3D.h"

class Particle
{
public:
    using Position = wmath::Vector3D;

    Particle(double mass, double x, double y, double z);

    const Position &position() const;
    void setPosition(const Position &position);

    double mass() const;
    void setMass(double mass);

    const wmath::Vector3D &velocity() const;
    void setVelocity(const wmath::Vector3D &velocity);

private:
    double m_mass;
    Position m_position;
    wmath::Vector3D m_velocity;
};

typedef std::shared_ptr<Particle> ParticlePtr;
