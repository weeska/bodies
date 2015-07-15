#pragma once

#include <array>
#include <cmath>

namespace wmath {

template <class Content = double>
class Vector3D : public std::array<Content, 3>
{

public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) {
        this->setX(x);
        this->setY(y);
        this->setZ(z);
    }

    double x() const { return std::get<0>(*this); }
    double y() const { return std::get<1>(*this); }
    double z() const { return std::get<2>(*this); }

    void setX(double x) { (*this)[0] = x; }
    void setY(double y) { (*this)[1] = y; }
    void setZ(double z)  { (*this)[2] = z; }

    Vector3D operator+(const Vector3D &rhs) const {
        Vector3D difference(*this);
        difference += rhs;

        return difference;
    }

    Vector3D operator-(const Vector3D &rhs) const {
        Vector3D difference(*this);
        difference -= rhs;

        return difference;
    }

    Vector3D operator*(double scalar) const {
        Vector3D copy(*this);
        copy[0] *= scalar;
        copy[1] *= scalar;
        copy[2] *= scalar;

        return copy;
    }

    Vector3D normalized() const {
        return Vector3D(*this).normalize();
    }

    Vector3D &normalize() {
        const double length_ = this->length();

        (*this)[0] /= length_;
        (*this)[1] /= length_;
        (*this)[2] /= length_;

        return *this;
    }

    double length() const
    {
        return std::sqrt(this->x() * this->x() + this->y() * this->y() + this->z() * this->z());
    }

    Vector3D &operator-=(const Vector3D &other)
    {
        (*this)[0] -= other[0];
        (*this)[1] -= other[1];
        (*this)[2] -= other[2];

        return *this;
    }

    Vector3D &operator+=(const Vector3D &other)
    {
        (*this)[0] += other[0];
        (*this)[1] += other[1];
        (*this)[2] += other[2];

        return *this;
    }

    Vector3D &operator*=(const Vector3D &other)
    {
        (*this)[0] *= other[0];
        (*this)[1] *= other[1];
        (*this)[2] *= other[2];

        return *this;
    }
};

typedef Vector3D<double> Vector3Dd;

}
