#include "SpaceAccumulator.h"

#include <cmath>
#include <thread>
#include <vector>

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
