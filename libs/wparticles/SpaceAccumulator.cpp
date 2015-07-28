#include "SpaceAccumulator.h"

#include <cmath>
#include <thread>
#include <vector>

inline double sqrLength(const wmath::Vec3d &from, const wmath::Vec3d &to) {
    return (std::pow(to[0] - from[0], 2.0) +
        std::pow(to[1] - from[1], 2.0) +
        std::pow(to[2] - from[2], 2.0));
}

void SpaceAccumulator::accelerateParticle(const wmath::Vec3d &influencePosition, double influenceMass, const wmath::Vec3d &targetPosition, wmath::Vec3d &targetAcceleration) {

    const double sqrDifference = sqrLength(targetPosition, influencePosition);
    if(sqrDifference < 25.0) {
        return;
    }

    const double invr = 1.0/std::sqrt(sqrDifference);
    const double invr3 = invr * invr * invr;
    const double f = influenceMass * invr3;

    targetAcceleration[0] += f * (influencePosition[0] - targetPosition[0]);
    targetAcceleration[1] += f * (influencePosition[1] - targetPosition[1]);
    targetAcceleration[2] += f * (influencePosition[2] - targetPosition[2]);
}

void SpaceAccumulator::accumulate(std::vector<ParticlePtr> &particles)
{
    static const int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

    const int elements_per_thread = std::ceil(particles.size()/num_threads);
    for(int i = 0; i < num_threads; ++i) {
        const int start = i * elements_per_thread;
        const int end = (start + elements_per_thread) % (particles.size() + 1);
        threads.push_back(std::thread(&SpaceAccumulator::doAccumulateEffects, this, std::ref(particles), start, end));
    }

    std::for_each(std::begin(threads), std::end(threads), [](std::thread &t) {t.join();});
}
