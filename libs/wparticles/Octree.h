#pragma once

#include <array>
#include "wparticles/Particle.h"


class Octree
{
    const wmath::Vec3d m_center;
    const wmath::Vec3d m_halfEdge;

    ParticlePtr m_particle;
    std::array<Octree *, 8> m_children;
public:
    Octree(const wmath::Vec3d &center, double halfEdgeLength);
    ~Octree();

    const std::array<Octree *, 8> &children() const;

    bool isLeaf() const;
    bool hasData() const;

    const wmath::Vec3d &center() const;
    double halfEdgeLength() const;

    void insert(const ParticlePtr &newParticle);
    int octantIndex(const wmath::Vec3d &position) const;

    void particlesInside(const wmath::Vec3d &min, const wmath::Vec3d &max, std::vector<ParticlePtr> &particles) const;
    void reset();
    void computeMeans();
};
