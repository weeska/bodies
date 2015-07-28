#pragma once

#include "Octree.h"
#include "SpaceAccumulator.h"

class BarnesHutAccumulator : public SpaceAccumulator
{
public:
    BarnesHutAccumulator(const Octree &octree);
    void doAccumulateEffects(std::vector<ParticlePtr> &particles, int from, int to);

private:
    double maxDiameter(const Octree &cell) const;
    double pointToCellDistance(const Octree &cell, const wmath::Vec3d &position) const;

private:
    const Octree &m_octree;
};
