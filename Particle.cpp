#include "Particle.h"

Particle::Particle(double x, double y)
    : m_position(x, y, 0.0)
{

}

Particle::Position Particle::position() const
{
    return m_position;
}

void Particle::setPosition(Particle::Position position)
{
    m_position = position;
}

