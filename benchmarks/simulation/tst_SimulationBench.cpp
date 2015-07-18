#include <QString>
#include <QtTest>

#include <random>

#include "wparticles/Space.h"

class SimulationBench : public QObject
{
    Q_OBJECT

    Space m_space;
public:
    SimulationBench();

private Q_SLOTS:
    void bench();
};

SimulationBench::SimulationBench()
{
    m_space.clear();

    std::random_device device;
    std::mt19937 gen(device());
    gen.seed(1);
    std::uniform_real_distribution<double> dist;

    const int N = 10000;
    for(int i = 0; i < N; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        double z = 0.0;

        x = x * N * 1.0 - N * 0.5;
        y = y * N * 1.0 - N * 0.5;

        ParticlePtr p = std::make_shared<Particle>(10e8, x, y, z);
        m_space.addParticle(p);
    }
}

void SimulationBench::bench()
{
    QBENCHMARK {
        m_space.tick();
    }
}

QTEST_APPLESS_MAIN(SimulationBench)

#include "tst_SimulationBench.moc"
