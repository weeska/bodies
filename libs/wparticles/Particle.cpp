#include "Particle.h"

Particle::Particle(double mass, double x, double y, double z)
    : m_mass(mass)
    , m_position(x, y, z)
    , m_velocity(0.0)
{

}

const Particle::Position &Particle::position() const
{
    return m_position;
}

void Particle::setPosition(const Position &position)
{
    m_position = position;
}
double Particle::mass() const
{
    return m_mass;
}

void Particle::setMass(double mass)
{
    m_mass = mass;
}
const wmath::Vector3D &Particle::velocity() const
{
    return m_velocity;
}

void Particle::setVelocity(const wmath::Vector3D &velocity)
{
    m_velocity = velocity;
}


