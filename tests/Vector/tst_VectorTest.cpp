#include <QString>
#include <QtTest>

#include <QDebug>

#include "wmath/Vector.h"

class VectorTest : public QObject
{
    Q_OBJECT

public:
    VectorTest();

private Q_SLOTS:
    void lengthTest();
    void normalizeTest();
    void testContructors();
};

VectorTest::VectorTest() {

}

void VectorTest::testContructors()
{
    wmath::Vec3d vec(1.0, 2.0, 3.0);
    QCOMPARE(vec[0], 1.0);
    QCOMPARE(vec[1], 2.0);
    QCOMPARE(vec[2], 3.0);

    wmath::Vec3d vec2;
    QCOMPARE(vec2[0], 0.0);
    QCOMPARE(vec2[1], 0.0);
    QCOMPARE(vec2[2], 0.0);
}

void VectorTest::lengthTest()
{
    wmath::Vec3d vec(1.0, 2.0, 3.0);
    QCOMPARE(vec.length(), std::sqrt(14.0));
    QCOMPARE(vec.sqr_length(), 14.0);
}

void VectorTest::normalizeTest()
{
    wmath::Vec2d vec(1.0, 1.0);
    vec.normalize();
    QCOMPARE(vec.length(), 1.0);
}

QTEST_APPLESS_MAIN(VectorTest)

#include "tst_VectorTest.moc"
