#pragma once

namespace Math {

class Vector3D
{
public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);
    Vector3D(const Vector3D &other);

    double x() const;
    double y() const;
    double z() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    Vector3D operator+(const Vector3D &rhs) const;
    Vector3D operator-(const Vector3D &rhs) const;
    Vector3D operator*(double scalar) const;
    Vector3D normalized() const;

    Vector3D &operator-=(const Vector3D &other);
    Vector3D &operator+=(const Vector3D &other);
    Vector3D &operator*=(const Vector3D &other);

    Vector3D &normalize();


    double length() const;

private:
    double m_x;
    double m_y;
    double m_z;
};

}
