#include "NaiveAccumulator.h"

void NaiveAccumulator::doAccumulateEffects(std::vector<ParticlePtr> &particles, int from, int to)
{
    for(int i=from; i < to; ++i) {
        ParticlePtr &targetParticle = particles[i];
        targetParticle->velocity() *= 0.9;

        for(const ParticlePtr &influencingParticle : particles) {
            this->accelerateParticle(influencingParticle->constPosition(), influencingParticle->mass(),
                               targetParticle->constPosition(), targetParticle->acceleration());
        }
    }
}
