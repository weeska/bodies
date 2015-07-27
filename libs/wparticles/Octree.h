#pragma once

#include <array>
#include "wparticles/Particle.h"

class Octree
{
public:
    using OctreeChildren = std::array<std::shared_ptr<Octree>, 8>;
    using Position = wmath::Vec3d;

    Octree(const Position &center, double halfEdgeLength);
    const OctreeChildren &children() const;

    bool isLeaf() const;
    bool hasData() const;

    const Position &center() const;
    double halfEdgeLength() const;
    double meanMass() const;
    const Position &meanPosition() const;
    void particlesInside(const Position &min, const Position &max, std::vector<ParticlePtr> &particles) const;

    int octantIndex(const Position &position) const;

    void insert(const ParticlePtr &newParticle);
    void reset();
    void computeMeans();

private:
    const Position m_center;
    const Position m_halfEdge;

    Position m_meanPosition;
    double m_meanMass;

    ParticlePtr m_particle;
    OctreeChildren m_children;
};
