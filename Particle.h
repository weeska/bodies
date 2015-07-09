#pragma once

#include <memory>
#include <utility>

class Particle
{
public:
    using Position = std::pair<double, double>;

    Particle(double x, double y);
    ~Particle();

    Position position() const;
    void setPosition(Position position);

private:
    Position m_position;
};

typedef std::shared_ptr<Particle> ParticlePtr;
