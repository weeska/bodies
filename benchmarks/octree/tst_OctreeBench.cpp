#include <QString>
#include <QtTest>

#include "wparticles/UniformParticleGenerator.h"
#include "wparticles/Octree.h"

class OctreeBench : public QObject
{
    Q_OBJECT
public:
    OctreeBench();

private Q_SLOTS:
    void bench();
};

OctreeBench::OctreeBench()
{
}

void OctreeBench::bench()
{
    std::vector<ParticlePtr> particles;
    UniformParticleGenerator generator(10000, 1);
    generator.generate(particles);

    QBENCHMARK {
        Octree tree(wmath::Vec3d(), 1000.0);
        for(auto p : particles) {
            tree.insert(p);
        }
        tree.computeMeans();
    }
}

QTEST_APPLESS_MAIN(OctreeBench)

#include "tst_OctreeBench.moc"
