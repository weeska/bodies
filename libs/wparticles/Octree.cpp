#include "Octree.h"

#include <cassert>
#include <iostream>


bool pointInCube(const Octree::Vector &min, const Octree::Vector &max, const Octree::Vector &point)
{
    if(min[0] > point[0]) return false;
    if(min[1] > point[1]) return false;
    if(min[2] > point[2]) return false;

    if(point[0] > max[0]) return false;
    if(point[1] > max[1]) return false;
    if(point[2] > max[2]) return false;

    return true;
}

const Octree::Vector &Octree::center() const
{
    return m_center;
}

Octree::Octree(const Vector &center, double halfEdgeLength, int depth)
    : m_center(center)
    , m_halfEdge(halfEdgeLength, halfEdgeLength, halfEdgeLength)
    , m_depth(depth)
    , m_min(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max())
    , m_max(std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min())
    , m_meanMass()
    , m_children()
{
}

void Octree::reset()
{
    for(auto &c : m_children ) {
        c.reset();
    }

    m_particle.reset();
    m_min = Vector(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    m_max = Vector(std::numeric_limits<double>::min(), std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
}

wmath::Vec3d meanOfMeans(const wmath::Vec3d &v1, const wmath::Vec3d &v2, double n1, double n2) {
    if(n1 == 0) return v2 / n2;
    if(n2 == 0) return v1 / n1;

    return std::move(v1 * n1 / (n1+n2) + v2 * n2 / (n1+n2));
}

int Octree::computeMeanFromChilds()
{
    assert(!this->isLeaf());

    m_meanMass = 0.0;
    m_meanPosition = Vector();
    int cellsUsed = 0;

    for(const std::shared_ptr<Octree> &child : m_children) {
        int childCellsUsed = child->computeMeans();
        m_meanPosition = meanOfMeans(m_meanPosition, child->meanPosition(), cellsUsed, childCellsUsed);
        m_meanMass += child->meanMass();

        cellsUsed += childCellsUsed;
    }

    return cellsUsed;
}

int Octree::computeMeans()
{
    if(this->isLeaf()) {
        if(this->hasData()) {
            m_meanMass = m_particle->mass();
            m_meanPosition = m_particle->position();
            return 1;
        }
        return 0;
    }
    else return this->computeMeanFromChilds();
}

const Octree::Vector &Octree::min() const
{
    return m_min;
}
const Octree::Vector &Octree::max() const
{
    return m_max;
}

double Octree::meanMass() const
{
    return m_meanMass;
}

const Octree::Vector &Octree::meanPosition() const
{
    return m_meanPosition;
}

const Octree::OctreeChildren &Octree::children() const
{
    return m_children;
}

bool Octree::isLeaf() const
{
    return (m_children[0] == nullptr);
}

bool Octree::hasData() const
{
    return (m_particle.get() != nullptr);
}

const ParticlePtr &Octree::data() const
{
    return m_particle;
}

double Octree::halfEdgeLength() const
{
    return m_halfEdge[0];
}

void Octree::updateMinMax(const ParticlePtr &particle)
{
    const wmath::Vec3d &pos = particle->constPosition();

    m_min[0] = std::min(pos[0], m_min[0]);
    m_min[1] = std::min(pos[1], m_min[1]);
    m_min[2] = std::min(pos[2], m_min[2]);

    m_max[0] = std::max(pos[0], m_max[0]);
    m_max[1] = std::max(pos[1], m_max[1]);
    m_max[2] = std::max(pos[2], m_max[2]);

}

bool Octree::particlesTooClose(const ParticlePtr &p1, const ParticlePtr &p2) {
    if(p1 == p2) return true;

    const wmath::Vec3d &pos1 = p1->constPosition();
    const wmath::Vec3d &pos2 = p2->constPosition();

    if(std::abs(pos1[0] - pos2[0]) < std::abs(m_halfEdge[0]) * 0.1) return true;
    if(std::abs(pos1[1] - pos2[1]) < std::abs(m_halfEdge[1]) * 0.1) return true;
    if(std::abs(pos1[2] - pos2[2]) < std::abs(m_halfEdge[2]) * 0.1) return true;

    return false;
}

ParticlePtr Octree::mergeParticles(const ParticlePtr p1, const ParticlePtr p2)
{
    if(p1 == p2) return p1;

    const wmath::Vec3d &pos = (p1->constPosition() + p2->constPosition()) * 0.5;
    return std::make_shared<Particle>(p1->mass() + p2->mass(), pos[0], pos[1], pos[2]);
}

void Octree::insert(const ParticlePtr &newParticle)
{
    if(this->isLeaf()) {
        if(!this->hasData()) {
            m_particle = newParticle;

            this->updateMinMax(newParticle);
        }
        else {
            ParticlePtr oldParticle = m_particle;
            m_particle.reset();

            for(int i = 0; i < 8; ++i) {
                Vector subCenter(m_center);
                subCenter[0] += m_halfEdge[0] * ( (i & 1) ? 0.5 : -0.5);
                subCenter[1] += m_halfEdge[1] * ( (i & 2) ? 0.5 : -0.5);
                subCenter[2] += m_halfEdge[2] * ( (i & 4) ? 0.5 : -0.5);

                m_children[i].reset(new Octree(subCenter, m_halfEdge[0] * 0.5, m_depth + 1));
            }

            const int newParticleIndex = this->octantIndex(newParticle->position());
            const int oldParticleIndex = this->octantIndex(oldParticle->position());

            if(m_depth > 5 || this->particlesTooClose(newParticle, oldParticle)) {
                m_children[newParticleIndex]->insert(this->mergeParticles(oldParticle, newParticle));
            }
            else {
                m_children[oldParticleIndex]->insert(oldParticle);
                m_children[newParticleIndex]->insert(newParticle);
            }
        }
    }
    else {
        const int newParticleIndex = this->octantIndex(newParticle->position());
        m_children[newParticleIndex]->insert(newParticle);
    }
}

int Octree::octantIndex(const Vector &position) const
{
    int idx = 0;
    if(position[0] >= m_center[0]) idx |= 1;
    if(position[1] >= m_center[1]) idx |= 2;
    if(position[2] >= m_center[2]) idx |= 4;
    return idx;
}

void Octree::particlesInside(const Vector &min, const Vector &max, std::vector<ParticlePtr> &particles) const
{
    if(this->isLeaf()) {
        if(this->hasData()) {
            if(pointInCube(min, max, m_particle->position())) {
                particles.push_back(m_particle);
            }
        }
    }
    else {
        for(int i=0; i<8; ++i) {
            const Vector &childMax = m_children[i]->m_center + m_children[i]->m_halfEdge;
            const Vector &childMin = m_children[i]->m_center - m_children[i]->m_halfEdge;

            if(childMax[0] < min[0] || childMax[1] < min[1] || childMax[2] < min[2]) continue;
            if(childMin[0] > max[0] || childMin[1] > max[1] || childMin[2] > max[2]) continue;

            m_children[i]->particlesInside(min, max, particles);
        }
    }
}

