#include "Attraction.h"

#include <cmath>
#include "Particle.h"

Attraction::Attraction(double strength, const wmath::Vector3Dd &position)
    : m_strength(strength)
    , m_target(position)
{

}

wmath::Vector3Dd Attraction::effect(const Particle &particle) const
{
    const wmath::Vector3Dd &position = particle.constPosition();
    const wmath::Vector3Dd &difference = (m_target - position);
    const wmath::Vector3Dd &direction = difference.normalized();

    return direction * std::pow(m_strength , 1.0 / difference.sqr_length());
}
