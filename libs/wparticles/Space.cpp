#include "Space.h"
#include <cassert>
#include <thread>
#include <future>
static const double dt = 0.0001;

void accumulateEffects(std::vector<ParticlePtr> &particles, int from, int to)
{
    for(int i=from; i < to; ++i) {
        ParticlePtr p_i = particles[i];
        wmath::Vec3d &acceleration = p_i->acceleration();
        p_i->velocity() *= 0.9;
        acceleration.fill(0.0);

        for(ParticlePtr p_j: particles) {
            const wmath::Vec3d &constPosition = p_i->constPosition();
            const wmath::Vec3d &constTargetPosition = p_j->constPosition();
            wmath::Vec3d difference;

            difference[0] = constTargetPosition[0] - constPosition[0];
            difference[1] = constTargetPosition[1] - constPosition[1];
            difference[2] = constTargetPosition[2] - constPosition[2];

            if(difference.sqr_length() < 25.0) {
                continue;
            }

            const double invr = 1.0/difference.length();
            const double invr3 = invr * invr * invr;
            const double f = p_j->mass() * invr3;

            acceleration[0] += f * difference[0];
            acceleration[1] += f * difference[1];
            acceleration[2] += f * difference[2];
        }
    }
}

void Space::applyEffects()
{
    for(ParticlePtr particle : m_particles) {
        wmath::Vec3d &position = particle->position();
        wmath::Vec3d &velocity = particle->velocity();
        wmath::Vec3d &acceleration = particle->acceleration();

        for(int i=0; i < 3; ++i) {
            position[i] += dt * velocity[i] + 0.5 * dt * dt * acceleration[i];
            velocity[i] += dt * acceleration[i];
        }
    }
}

void Space::tick()
{
    static const int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

    const int elements_per_thread = std::ceil(m_particles.size()/num_threads);
    for(int i = 0; i < num_threads; ++i) {
        const int start = i * elements_per_thread;
        const int end = (start + elements_per_thread) % (m_particles.size() + 1);
        threads.push_back(std::thread(accumulateEffects, std::ref(m_particles), start, end));
    }

    std::for_each(std::begin(threads), std::end(threads), [](std::thread &t) {t.join();});

    this->applyEffects();
}

std::vector<ParticlePtr> &Space::particles()
{
    return m_particles;
}

const std::vector<ParticlePtr> &Space::constParticles() const
{
    return m_particles;
}

