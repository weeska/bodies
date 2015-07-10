#include "Attraction.h"

#include "Particle.h"

Attraction::Attraction(double strength, const Math::Vector3D &position)
    : m_strength(strength)
    , m_target(position)
{

}

Math::Vector3D Attraction::effect(const Particle &particle) const
{
    const Math::Vector3D position = particle.position();
    const Math::Vector3D difference = (m_target - position);
    const Math::Vector3D direction = difference.normalized();

    return direction * std::pow(m_strength , 1.0 / difference.length());
}
