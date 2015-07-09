#include "Particle.h"

Particle::Particle(double x, double y)
    : m_position(std::pair<double, double>(x, y))
{

}

Particle::~Particle()
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

