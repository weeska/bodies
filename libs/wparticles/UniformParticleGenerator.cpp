#include "UniformParticleGenerator.h"

void UniformParticleGenerator::setSeed(uint_fast32_t seed)
{
    m_seed = seed;
}

void UniformParticleGenerator::setParticleCount(size_t particleCount)
{
    m_particleCount = particleCount;
}

UniformParticleGenerator::UniformParticleGenerator(size_t count, uint_fast32_t seed)
    : m_particleCount(count)
    , m_seed(seed) {}

void UniformParticleGenerator::generate(Space &space) const
{
    space.resetData();
    space.reserve(m_particleCount);

    std::random_device device;
    std::mt19937 gen(device());
    gen.seed(m_seed);
    std::uniform_real_distribution<double> dist;

    for(size_t i = 0; i < m_particleCount; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        double z = 0.0;

        x = x * 2000.0 - 1000.0;
        y = y * 2000.0 - 1000.0;

        space.addParticleData(wmath::Vec3d(x, y, z),
                              x > 0 ? wmath::Vec3d(0.0, 0.5, 1.0) : wmath::Vec3d(0.0, 1.0, 0.5),
                              10e8);
    }
}
