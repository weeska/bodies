#pragma once

#include <array>
#include "wparticles/Particle.h"

class Octree
{
public:
    using OctreeChildren = std::array<std::shared_ptr<Octree>, 8>;
    using Vector = wmath::Vec3d;

    Octree(const Vector &center, double halfEdgeLength);
    const OctreeChildren &children() const;

    bool isLeaf() const;
    bool hasData() const;

    const ParticlePtr &data() const;
    const Vector &center() const;
    double halfEdgeLength() const;

    double meanMass() const;
    const Vector &meanPosition() const;
    void particlesInside(const Vector &min, const Vector &max, std::vector<ParticlePtr> &particles) const;

    int octantIndex(const Vector &position) const;

    void insert(const ParticlePtr &newParticle);
    void reset();
    void computeMeans();

    const Vector &min() const;
    const Vector &max() const;

    void updateMinMax(const ParticlePtr &particle);
private:
    const Vector m_center;
    const Vector m_halfEdge;

    Vector m_min;
    Vector m_max;
    Vector m_meanPosition;
    double m_meanMass;

    ParticlePtr m_particle;
    OctreeChildren m_children;
};
