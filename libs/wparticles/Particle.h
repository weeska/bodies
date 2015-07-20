#pragma once

#include <memory>
#include <utility>

#include "wmath/Vector.h"

class Particle
{
public:
    Particle(double mass, double x, double y, double z);

    const wmath::Vec3d &constColor() const;
    const wmath::Vec3d &constPosition() const;
    const wmath::Vec3d &constVelocity() const;

    double mass() const;
    wmath::Vec3d &acceleration();
    wmath::Vec3d &position();
    wmath::Vec3d &velocity();

    void setMass(double mass);
    void setAcceleration(const wmath::Vec3d &acceleration);
    void setColor(const wmath::Vec3d &constColor);
    void setPosition(const wmath::Vec3d &position);
    void setVelocity(const wmath::Vec3d &constVelocity);


private:
    double m_mass;
    wmath::Vec3d m_acceleration;
    wmath::Vec3d m_color;
    wmath::Vec3d m_position;
    wmath::Vec3d m_velocity;
};

typedef std::shared_ptr<Particle> ParticlePtr;
