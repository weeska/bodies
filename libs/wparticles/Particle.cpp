#include "Particle.h"

Particle::Particle(double mass, double x, double y, double z)
    : m_mass(mass)
    , m_position(x, y, z)
    , m_velocity()
{

}

const Particle::Position &Particle::constPosition() const
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
const wmath::Vector3Dd &Particle::constVelocity() const
{
    return m_velocity;
}

void Particle::setVelocity(const wmath::Vector3Dd &velocity)
{
    m_velocity = velocity;
}


