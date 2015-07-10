#include "Vector3D.h"

#include <cmath>

using namespace Math;

Vector3D::Vector3D(double x, double y, double z)
    : m_x(x)
    , m_y(y)
    , m_z(z)
{

}

Vector3D::Vector3D(const Vector3D &other)
    : m_x(other.x())
    , m_y(other.y())
    , m_z(other.z())
{

}

double Vector3D::x() const
{
    return m_x;
}

void Vector3D::setX(double x)
{
    m_x = x;
}
double Vector3D::y() const
{
    return m_y;
}

void Vector3D::setY(double y)
{
    m_y = y;
}
double Vector3D::z() const
{
    return m_z;
}

void Vector3D::setZ(double z)
{
    m_z = z;
}

Vector3D Vector3D::operator*(double scalar) const
{
    Vector3D copy(*this);
    copy.m_x *= scalar;
    copy.m_y *= scalar;
    copy.m_z *= scalar;

    return copy;
}

Vector3D Vector3D::normalized() const
{
    return Vector3D(*this).normalize();
}

Vector3D Vector3D::operator-(const Vector3D &rhs) const
{
    Vector3D difference(*this);
    difference -= rhs;

    return difference;
}

Vector3D Vector3D::operator+(const Vector3D &rhs) const
{
    Vector3D difference(*this);
    difference += rhs;

    return difference;
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;

    return *this;
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;

    return *this;
}

Vector3D &Vector3D::operator*=(const Vector3D &other)
{
    m_x *= other.m_x;
    m_y *= other.m_y;
    m_z *= other.m_z;

    return *this;
}

Vector3D &Vector3D::normalize()
{
    const double length_ = this->length();

    m_x /= length_;
    m_y /= length_;
    m_z /= length_;

    return *this;
}

double Vector3D::length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}




