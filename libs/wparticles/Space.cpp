#include "Space.h"

#include "Attraction.h"
#include "AttractionToParticle.h"

#include <map>

Space::Space()
{
    //this->addForce(std::make_shared<Attraction>(1.0, wmath::Vector3D()));
}

void Space::addForce(ForcePtr force)
{
    m_forces.push_back(force);
}

void Space::addParticle(ParticlePtr particle)
{
    m_particles.push_back(particle);
    this->addForce(std::make_shared<AttractionToParticle>(*this));
}

double newPosition(double current, double velocity, double step, double acceleration) {
    return current + step * velocity + 0.5 * step * step * acceleration;
}

double newVelocity(double current, double step, double acceleration) {
    return current + step * acceleration;
}

void Space::tick()
{
    static const double dt = 1.0;
    std::map<ParticlePtr, wmath::Vector3D> accelerations;

    for(ParticlePtr p : *this) {
        wmath::Vector3D effect;

        for(ForcePtr force : m_forces) {
            effect += force->effect(*p);
        }

        accelerations[p] = effect;
    }

    for(std::pair<ParticlePtr, wmath::Vector3D> f : accelerations) {
        const wmath::Vector3D &position = f.first->position();
        const wmath::Vector3D &velocity = f.first->velocity();
        const wmath::Vector3D &a = f.second;
        wmath::Vector3D new_position;
        wmath::Vector3D new_velocity;

        new_position.setX( newPosition( position.x(), velocity.x(), dt, a.x()) );
        new_position.setY( newPosition( position.y(), velocity.y(), dt, a.y()) );
        new_position.setZ( newPosition( position.z(), velocity.z(), dt, a.z()) );

        new_velocity.setX( newVelocity( velocity.x(), dt, a.x() ));
        new_velocity.setY( newVelocity( velocity.y(), dt, a.y() ));
        new_velocity.setZ( newVelocity( velocity.z(), dt, a.z() ));

        f.first->setPosition(new_position);
        f.first->setVelocity(new_velocity);
    }
}

Space::ParticleIterator Space::begin()
{
    return m_particles.begin();
}

Space::ParticleIterator Space::end()
{
    return m_particles.end();
}

