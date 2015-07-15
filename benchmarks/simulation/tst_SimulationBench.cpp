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
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_real_distribution<double> dist;

    for(int i = 0; i < 250; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        double z = 0.0;

        x = x * 2.0 - 1.0;
        y = y * 2.0 - 1.0;

        m_space.addParticle(std::make_shared<Particle>(0.1, x, y, z));
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
