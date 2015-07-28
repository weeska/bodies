#include <QString>
#include <QtTest>

#include <random>

#include "wparticles/Octree.h"
#include "wparticles/Space.h"
#include "wparticles/BarnesHutAccumulator.h"
#include "wparticles/NaiveAccumulator.h"
#include "wparticles/UniformParticleGenerator.h"

class SimulationBench : public QObject
{
    Q_OBJECT

public:
    SimulationBench();

private Q_SLOTS:
    void barnesHutBench();
    void naiveBench();
};

SimulationBench::SimulationBench()
{
}

void SimulationBench::naiveBench()
{
    Space space;
    UniformParticleGenerator generator(10000, 1);
    generator.generate(space.particles());

    space.setAccumulator(new NaiveAccumulator);

    QBENCHMARK {
        space.tick();
    }
}

void SimulationBench::barnesHutBench()
{
    Space space;
    UniformParticleGenerator generator(10000, 1);
    generator.generate(space.particles());

    Octree tree(wmath::Vec3d(), 1000.0);
    space.setAccumulator(new BarnesHutAccumulator(tree));

    QBENCHMARK {

        for(auto p : space.particles()) {
            tree.insert(p);
        }
        tree.computeMeans();

        space.tick();
    }
}

QTEST_APPLESS_MAIN(SimulationBench)

#include "tst_SimulationBench.moc"
