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
    void testContructors();
    void testPlusOperators();
    void testMinusOperators();
    void testMultOperators();
};

VectorTest::VectorTest() {

}

void VectorTest::testContructors()
{
    wmath::Vector3D<double> vector;
    QCOMPARE(vector[0], 0.0);
    QCOMPARE(vector[1], 0.0);
    QCOMPARE(vector[2], 0.0);

    wmath::Vector3D<double> vector2(1.0, 2.0, 3.0);
    QCOMPARE(vector2[0], 1.0);
    QCOMPARE(vector2[1], 2.0);
    QCOMPARE(vector2[2], 3.0);
}

void VectorTest::testMinusOperators()
{
    wmath::Vector3D<double> v1(1.0, 1.0, 1.0), v2(1.0, 1.0, 1.0);

    QCOMPARE(v1 - v2, wmath::Vector3Dd());
    v1 -= v2;
    QCOMPARE(v1, wmath::Vector3Dd());
}

void VectorTest::testPlusOperators()
{
    wmath::Vector3D<double> v1(1.0, 1.0, 1.0), v2(1.0, 1.0, 1.0);

    QCOMPARE(v1 + v2, wmath::Vector3Dd(2.0, 2.0, 2.0));
    v1 += v2;
    QCOMPARE(v1, wmath::Vector3Dd(2.0, 2.0, 2.0));
}

void VectorTest::testMultOperators()
{
    wmath::Vector3D<double> v1(2.0, 3.0, 4.0);

    QCOMPARE(v1 * 3.0, wmath::Vector3Dd(6.0, 9.0, 12.0));
    v1 *= 3.0;

    QCOMPARE(v1, wmath::Vector3Dd(6.0, 9.0, 12.0));
}

QTEST_APPLESS_MAIN(VectorTest)

#include "tst_VectorTest.moc"
