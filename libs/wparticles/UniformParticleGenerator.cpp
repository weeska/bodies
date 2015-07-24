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

void UniformParticleGenerator::generate(std::vector<ParticlePtr> &particles) const
{
    particles.clear();

    std::random_device device;
    std::mt19937 gen(device());
    gen.seed(m_seed);
    std::uniform_real_distribution<double> dist;

    for(size_t i = 0; i < m_particleCount; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        double z = dist(gen);

        x = x * 2000.0 - 1000.0;
        y = y * 2000.0 - 1000.0;
        z = z * 200.0 - 100.0;

        ParticlePtr p = std::make_shared<Particle>(10e8, x, y, z);
        if(x < 0.0) {
            p->setColor(wmath::Vec3d(0.0, 1.0, 0.5));
        }
        else {
            p->setColor(wmath::Vec3d(0.0, 0.5, 1.0));
        }
        particles.push_back(p);
    }
}
