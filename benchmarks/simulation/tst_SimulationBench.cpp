#include <QString>
#include <QtTest>

#include <random>

#include "wparticles/Space.h"
#include "wparticles/UniformParticleGenerator.h"

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
    UniformParticleGenerator generator(10000, 1);
    generator.generate(m_space.particles());
}

void SimulationBench::bench()
{
    QBENCHMARK {
        m_space.tick();
    }
}

QTEST_APPLESS_MAIN(SimulationBench)

#include "tst_SimulationBench.moc"
