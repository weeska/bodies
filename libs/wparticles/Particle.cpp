#include "Particle.h"

Particle::Particle(double mass, double x, double y, double z)
    : m_mass(mass)
    , m_position(x, y, z)
    , m_velocity()
{

}

wmath::Vector3Dd &Particle::position() {
    return m_position;
}

wmath::Vector3Dd &Particle::velocity() {
    return m_velocity;
}

const wmath::Vector3Dd &Particle::constPosition() const
{
    return m_position;
}

void Particle::setPosition(const wmath::Vector3Dd &position)
{
    m_position = position;
}
double Particle::mass() const
{
    return m_mass;
}

wmath::Vector3Dd &Particle::acceleration()
{
    return m_acceleration;
}

void Particle::setMass(double mass)
{
    m_mass = mass;
}

void Particle::setAcceleration(const wmath::Vector3Dd &acceleration)
{
    m_acceleration = acceleration;
}
const wmath::Vector3Dd &Particle::constVelocity() const
{
    return m_velocity;
}

void Particle::setVelocity(const wmath::Vector3Dd &velocity)
{
    m_velocity = velocity;
}
const wmath::Vector3Dd &Particle::constColor() const
{
    return m_color;
}

void Particle::setColor(const wmath::Vector3Dd &color)
{
    m_color = color;
}

