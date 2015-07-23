#include "Particle.h"

Particle::Particle(double mass, double x, double y, double z)
    : m_mass(mass)
    , m_position(x, y, z)
    , m_velocity()
{

}

wmath::Vec3d &Particle::position() {
    return m_position;
}

wmath::Vec3d &Particle::velocity() {
    return m_velocity;
}

const wmath::Vec3d &Particle::constPosition() const
{
    return m_position;
}

void Particle::setPosition(const wmath::Vec3d &position)
{
    m_position = position;
}
double Particle::mass() const
{
    return m_mass;
}

wmath::Vec3d &Particle::acceleration()
{
    return m_acceleration;
}

void Particle::setMass(double mass)
{
    m_mass = mass;
}

void Particle::setAcceleration(const wmath::Vec3d &acceleration)
{
    m_acceleration = acceleration;
}
const wmath::Vec3d &Particle::constVelocity() const
{
    return m_velocity;
}

void Particle::setVelocity(const wmath::Vec3d &velocity)
{
    m_velocity = velocity;
}
const wmath::Vec3d &Particle::constColor() const
{
    return m_color;
}

void Particle::setColor(const wmath::Vec3d &color)
{
    m_color = color;
}

