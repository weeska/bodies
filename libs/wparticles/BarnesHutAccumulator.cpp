#include "BarnesHutAccumulator.h"

#include <queue>

BarnesHutAccumulator::BarnesHutAccumulator(const Octree &octree)
    : m_octree(octree)
{

}

void BarnesHutAccumulator::doAccumulateEffects(std::vector<ParticlePtr> &particles, int from, int to)
{
    for(int i = from; i < to; ++i) {
        ParticlePtr &particle = particles[i];

        std::queue<const Octree*> cells;
        cells.push(&m_octree);
        while(!cells.empty()) {
            const Octree *cell = cells.front();
            cells.pop();

            if(cell->isLeaf()) {
                if(cell->hasData() ) {
                    const ParticlePtr &influencingParticle = cell->data();
                    this->accelerateParticle(influencingParticle->constPosition(), influencingParticle->mass(),
                                             particle->constPosition(), particle->acceleration());
                }
            }
            else {
                const double groupDiameter = this->maxDiameter(*cell);
                const double groupDistance = this->pointToCellDistance(*cell, particle->constPosition());
                if(groupDistance == 0.0) {
                    continue;
                }

                const double theta = (groupDiameter / groupDistance);

                if(theta < 0.5) {
                    this->accelerateParticle(cell->meanPosition(), cell->meanMass(), particle->constPosition(), particle->acceleration());
                }
                else {
                    for( auto child : cell->children()) {
                        cells.push(child.get());
                    }
                }
            }
        }
    }
}

double BarnesHutAccumulator::pointToCellDistance(const Octree &cell, const wmath::Vec3d &position) const {
    const Octree::Vector &center = cell.meanPosition();
    return std::sqrt(
        std::pow(center[0] - position[0], 2.0) +
        std::pow(center[1] - position[1], 2.0) +
        std::pow(center[2] - position[2], 2.0)
    );
}

double BarnesHutAccumulator::maxDiameter(const Octree &cell) const
{
    const Octree::Vector &min = cell.min();
    const Octree::Vector &max = cell.max();

    return std::max({max[0] - min[0], max[1] - min[1], max[2] - min[2]});
}

