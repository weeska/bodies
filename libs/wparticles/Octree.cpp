#include "Octree.h"


#include <iostream>

const Octree::Position &Octree::center() const
{
    return m_center;
}

Octree::Octree(const Position &center, double halfEdgeLength)
    : m_center(center)
    , m_halfEdge(halfEdgeLength, halfEdgeLength, halfEdgeLength)
    , m_meanMass()
    , m_children()
{
}

void Octree::reset()
{
    for( auto c : m_children ) {
        c.reset();
    }
    m_particle.reset();
}

void Octree::computeMeans()
{
    m_meanMass = 0.0;
    m_meanPosition = Position();

    if(this->isLeaf()) {
        if(this->hasData()) {
            m_meanMass = m_particle->mass();
            m_meanPosition = m_particle->position();
        }
    }
    else {
        int numChildsWithData = 0;
        for( auto child : m_children) {
            if(!child) {
                break;
            }

            if(child->hasData()) {
                ++numChildsWithData;
            }

            child->computeMeans();
            m_meanMass += child->meanMass();
            m_meanPosition += child->meanPosition();
        }

        m_meanMass /= std::max<float>(numChildsWithData, 1.0f);
        m_meanPosition /= std::max<float>(numChildsWithData, 1.0f);
    }
}

double Octree::meanMass() const
{
    return m_meanMass;
}

const Octree::Position &Octree::meanPosition() const
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

double Octree::halfEdgeLength() const
{
    return m_halfEdge[0];
}

void Octree::insert(const ParticlePtr &newParticle)
{
    if(this->isLeaf()) {
        if(!this->hasData()) {
            m_particle = newParticle;
        }
        else {
            ParticlePtr oldParticle = m_particle;
            m_particle.reset();

            for(int i = 0; i < 8; ++i) {
                Position subCenter(m_center);
                subCenter[0] += m_halfEdge[0] * ( (i & 1) ? 0.5 : -0.5);
                subCenter[1] += m_halfEdge[1] * ( (i & 2) ? 0.5 : -0.5);
                subCenter[2] += m_halfEdge[2] * ( (i & 4) ? 0.5 : -0.5);

                m_children[i].reset(new Octree(subCenter, m_halfEdge[0] * 0.5));
            }

            const int newParticleIndex = this->octantIndex(newParticle->position());
            const int oldParticleIndex = this->octantIndex(oldParticle->position());

            m_children[oldParticleIndex]->insert(oldParticle);
            if(oldParticle != newParticle) {
                m_children[newParticleIndex]->insert(newParticle);
            }
        }
    }
    else {
        const int newParticleIndex = this->octantIndex(newParticle->position());
        m_children[newParticleIndex]->insert(newParticle);
    }
}

int Octree::octantIndex(const Position &position) const
{
    int idx = 0;
    if(position[0] >= m_center[0]) idx |= 1;
    if(position[1] >= m_center[1]) idx |= 2;
    if(position[2] >= m_center[2]) idx |= 4;
    return idx;
}

bool pointInCube(const Octree::Position &min, const Octree::Position &max, const Octree::Position &point)
{
    if(min[0] > point[0]) return false;
    if(min[1] > point[1]) return false;
    if(min[2] > point[2]) return false;

    if(point[0] > max[0]) return false;
    if(point[1] > max[1]) return false;
    if(point[2] > max[2]) return false;

    return true;
}

void Octree::particlesInside(const Position &min, const Position &max, std::vector<ParticlePtr> &particles) const
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
            const Position &childMax = m_children[i]->m_center + m_children[i]->m_halfEdge;
            const Position &childMin = m_children[i]->m_center - m_children[i]->m_halfEdge;

            if(childMax[0] < min[0] || childMax[1] < min[1] || childMax[2] < min[2]) continue;
            if(childMin[0] > max[0] || childMin[1] > max[1] || childMin[2] > max[2]) continue;

            m_children[i]->particlesInside(min, max, particles);
        }
    }
}

