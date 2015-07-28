#pragma once

#include "Octree.h"
#include "SpaceAccumulator.h"

class BarnesHutAccumulator : public SpaceAccumulator
{
public:
    BarnesHutAccumulator(const Octree &octree);
    void doAccumulateEffects(int from, int to);

private:
    const Octree &m_octree;
};
