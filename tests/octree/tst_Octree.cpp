#include <QString>
#include <QtTest>
#include <array>

#include "wparticles/Octree.h"

enum Octant {
    TopFrontRight = 7,
    TopBackRight = 6,
    TopBackLeft = 4,
    TopFrontLeft = 5,
    BottomFrontRight = 3,
    BottomBackRight = 2,
    BottomBackLeft = 0,
    BottomFronLeft = 1
};

class OctreeTest : public QObject
{
    Q_OBJECT

public:
    OctreeTest();
private slots:
    void testNewIsEmpty();
    void testInsert();
    void testSimpleComputeMeans();
    void testComputeMeans();
    void testInsertSplit();
    void testOctantIndex();
};

OctreeTest::OctreeTest()
{
}

void OctreeTest::testNewIsEmpty()
{
    Octree tree(wmath::Vec3d(0.0, 0.0, 0.0), 1.0);

    QVERIFY(!tree.hasData());
    QVERIFY(tree.isLeaf());
}

void OctreeTest::testInsert()
{
    ParticlePtr particle = std::make_shared<Particle>(100.0, 0.5, 0.5, 0.5);

    Octree tree(wmath::Vec3d(0.0, 0.0, 0.0), 1.0);
    tree.insert(particle);

    QVERIFY(tree.isLeaf());
    QVERIFY(tree.hasData());

    std::vector<ParticlePtr> particles;
    tree.particlesInside(wmath::Vec3d(0.0, 0.0, 0.0), wmath::Vec3d(1.0, 1.0, 1.0), particles);

    QVERIFY( std::end(particles) != std::find(std::begin(particles), std::end(particles), particle));
}

void OctreeTest::testSimpleComputeMeans()
{
    Octree tree(wmath::Vec3d(0.0, 0.0, 0.0), 1.0);
    ParticlePtr p = std::make_shared<Particle>(100.0, 0.5, 0.5, 0.5);

    tree.insert(p);
    tree.computeMeans();

    QCOMPARE(tree.meanMass(), 100.0);
    QCOMPARE(tree.meanPosition(), p->position());
}

void OctreeTest::testComputeMeans()
{
    Octree tree(wmath::Vec3d(0.0, 0.0, 0.0), 1.0);

    ParticlePtr particle1 = std::make_shared<Particle>(100.0, 0.5, 0.5, 0.5);
    ParticlePtr particle2 = std::make_shared<Particle>(200.0, 0.75, 0.75, 0.75);

    tree.insert(particle1);
    tree.insert(particle2);
    tree.computeMeans();

    QCOMPARE(tree.meanMass(), 150.0);
    QCOMPARE(tree.meanPosition(), (particle1->position() + particle2->position()) * 0.5);
}

void OctreeTest::testInsertSplit()
{
    ParticlePtr particle1 = std::make_shared<Particle>(100.0, 0.5, 0.5, 0.5);
    ParticlePtr particle2 = std::make_shared<Particle>(100.0, 0.75, 0.75, 0.75);

    Octree tree(wmath::Vec3d(0.0, 0.0, 0.0), 1.0);
    tree.insert(particle1);

    QVERIFY(tree.isLeaf());
    tree.insert(particle2);
}

void OctreeTest::testOctantIndex()
{
    using namespace wmath;

    Octree tree(Vec3d(0.0, 0.0, 0.0), 1.0);

    QCOMPARE(tree.octantIndex(Vec3d(1.0, 1.0, 1.0)), static_cast<int>(Octant::TopFrontRight));
    QCOMPARE(tree.octantIndex(Vec3d(-1.0, 1.0, 1.0)), static_cast<int>(Octant::TopBackRight));

    QCOMPARE(tree.octantIndex(Vec3d(-1.0, -1.0, 1.0)), static_cast<int>(Octant::TopBackLeft));
    QCOMPARE(tree.octantIndex(Vec3d(1.0, -1.0, 1.0)), static_cast<int>(Octant::TopFrontLeft));

    QCOMPARE(tree.octantIndex(Vec3d(1.0, 1.0, -1.0)), static_cast<int>(Octant::BottomFrontRight));
    QCOMPARE(tree.octantIndex(Vec3d(-1.0, 1.0, -1.0)), static_cast<int>(Octant::BottomBackRight));

    QCOMPARE(tree.octantIndex(Vec3d(-1.0, -1.0, -1.0)), static_cast<int>(Octant::BottomBackLeft));
    QCOMPARE(tree.octantIndex(Vec3d(1.0, -1.0, -1.0)), static_cast<int>(Octant::BottomFronLeft));
}

QTEST_APPLESS_MAIN(OctreeTest)

#include "tst_Octree.moc"
