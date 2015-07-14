#include "Attraction.h"

#include <cmath>
#include "Particle.h"

Attraction::Attraction(double strength, const wmath::Vector3D &position)
    : m_strength(strength)
    , m_target(position)
{

}

wmath::Vector3D Attraction::effect(const Particle &particle) const
{
    const wmath::Vector3D &position = particle.position();
    const wmath::Vector3D &difference = (m_target - position);
    const wmath::Vector3D &direction = difference.normalized();

    const double length = difference.length();
    const double sqr_length = length * length;

    return direction * std::pow(m_strength , 1.0 / sqr_length);
}
