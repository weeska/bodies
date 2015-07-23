#include "Space.h"
#include <cassert>
#include <thread>
#include <future>
static const double dt = 0.0001;

inline double sqrLength(const wmath::Vec3d &from, const wmath::Vec3d &to) {
    return (std::pow(to[0] - from[0], 2.0) +
        std::pow(to[1] - from[1], 2.0) +
        std::pow(to[2] - from[2], 2.0));
}

void accumulateEffects(Space::Data &data, size_t from, size_t to)
{
    for(size_t i = from; i < to; ++i) {
        const wmath::Vec3d &constPosition = data.positions[i];
        wmath::Vec3d &acceleration = data.accelerations[i];
        data.velocities[i] *= 0.9;

        for(size_t j = 0; j < data.positions.size(); ++j) {
            const wmath::Vec3d &constTargetPosition = data.positions[j];

            const double sqrDifference = sqrLength(constPosition, constTargetPosition);
            if(sqrDifference < 25.0) {
                continue;
            }

            const double invr = 1.0/std::sqrt(sqrDifference);
            const double invr3 = invr * invr * invr;
            const double f = data.masses[i] * invr3;

            acceleration[0] += f * (constTargetPosition[0] - constPosition[0]);
            acceleration[1] += f * (constTargetPosition[1] - constPosition[1]);
            acceleration[2] += f * (constTargetPosition[2] - constPosition[2]);
        }
    }
}

void Space::applyEffects()
{
    for(size_t i = 0; i < this->particleCount(); ++i) {
        wmath::Vec3d &position = m_data.positions[i];
        wmath::Vec3d &velocity = m_data.velocities[i];
        wmath::Vec3d &acceleration = m_data.accelerations[i];

        for(int i=0; i < 3; ++i) {
            position[i] += dt * velocity[i] + 0.5 * dt * dt * acceleration[i];
            velocity[i] += dt * acceleration[i];
            acceleration[i] = 0.0;
        }
    }
}

void Space::tick()
{
    static const int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

    const int elements_per_thread = std::ceil(this->particleCount()/num_threads);
    for(int i = 0; i < num_threads; ++i) {
        const int start = i * elements_per_thread;
        const int end = (start + elements_per_thread) % (this->particleCount() + 1);
        threads.push_back(std::thread(accumulateEffects, std::ref(m_data), start, end));
    }

    std::for_each(std::begin(threads), std::end(threads), [](std::thread &t) {t.join();});

    this->applyEffects();
}

size_t Space::particleCount() const
{
    return m_data.positions.size();
}

const std::vector<wmath::Vec3d> &Space::accelerations() const
{
    return m_data.accelerations;
}

const std::vector<wmath::Vec3d> &Space::colors() const
{
    return m_data.colors;
}

const std::vector<wmath::Vec3d> &Space::positions() const
{
    return m_data.positions;
}

const std::vector<wmath::Vec3d> &Space::velocities() const
{
    return m_data.velocities;
}

void Space::addParticleData(const wmath::Vec3d &position, const wmath::Vec3d &color, double mass) {
    m_data.masses.push_back(mass);
    m_data.positions.push_back(position);
    m_data.colors.push_back(color);

    m_data.accelerations.push_back(wmath::Vec3d());
    m_data.velocities.push_back(wmath::Vec3d());
}

void Space::resetData()
{
    m_data = Space::Data();
}

void Space::reserve(size_t count)
{
    m_data.masses.reserve(count);
    m_data.accelerations.reserve(count);
    m_data.colors.reserve(count);
    m_data.positions.reserve(count);
    m_data.velocities.reserve(count);
}

