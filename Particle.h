#pragma once

#include <memory>
#include <utility>

#include "Vector3D.h"

class Particle
{
public:
    using Position = Math::Vector3D;

    Particle(double x, double y);

    Position position() const;
    void setPosition(Position position);

private:
    Position m_position;
};

typedef std::shared_ptr<Particle> ParticlePtr;
