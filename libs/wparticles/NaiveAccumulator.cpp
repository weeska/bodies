#include "NaiveAccumulator.h"

inline double sqrLength(const wmath::Vec3d &from, const wmath::Vec3d &to) {
    return (std::pow(to[0] - from[0], 2.0) +
        std::pow(to[1] - from[1], 2.0) +
        std::pow(to[2] - from[2], 2.0));
}

void NaiveAccumulator::doAccumulateEffects(std::vector<ParticlePtr> &particles, int from, int to)
{
    for(int i=from; i < to; ++i) {
        ParticlePtr &p_i = particles[i];
        const wmath::Vec3d &constPosition = p_i->constPosition();
        wmath::Vec3d &acceleration = p_i->acceleration();
        p_i->velocity() *= 0.9;

        for(const ParticlePtr &p_j: particles) {
            const wmath::Vec3d &constTargetPosition = p_j->constPosition();
            const double sqrDifference = sqrLength(constPosition, constTargetPosition);

            if(sqrDifference < 25.0) {
                continue;
            }

            const double invr = 1.0/std::sqrt(sqrDifference);
            const double invr3 = invr * invr * invr;
            const double f = p_j->mass() * invr3;

            acceleration[0] += f * (constTargetPosition[0] - constPosition[0]);
            acceleration[1] += f * (constTargetPosition[1] - constPosition[1]);
            acceleration[2] += f * (constTargetPosition[2] - constPosition[2]);
        }
    }
}
