#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

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

    void setX(double x) { (*this)[0] = x; }
    void setY(double y) { (*this)[1] = y; }
    void setZ(double z)  { (*this)[2] = z; }

    Vector3D operator+(const Vector3D &rhs) const {
        Vector3D difference(*this);
        difference += rhs;

        return std::move(difference);
    }

    Vector3D operator-(const Vector3D &rhs) const {
        Vector3D difference(*this);
        difference -= rhs;

        return std::move(difference);
    }

    Vector3D operator*(double scalar) const {
        Vector3D copy;
        std::transform(std::begin(*this), std::end(*this),
                       std::begin(copy),
                       [&](Content v) {return v * scalar;});

        return std::move(copy);
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

    double sqr_length() const
    {
        return std::pow((*this)[0], 2.0) +
                std::pow((*this)[1], 2.0) +
                std::pow((*this)[2], 2.0);
    }

    double length() const
    {
        return std::sqrt(this->sqr_length());
    }

    template <typename Func>
    void binaryAssignOp(const Vector3D &other, Func f) {
        std::transform(std::begin(*this), std::end(*this),
                       std::begin(other), std::begin(*this),
                       f);
    }

    Vector3D &operator-=(const Vector3D &other)
    {
        this->binaryAssignOp(other, std::minus<Content>());
        return *this;
    }

    Vector3D &operator+=(const Vector3D &other)
    {
        this->binaryAssignOp(other, std::plus<Content>());
        return *this;
    }

    Vector3D &operator*=(double scalar)
    {
        std::transform(std::begin(*this), std::end(*this),
                       std::begin(*this),
                       [&](Content v) {return v * scalar;});

        return *this;
    }

    Vector3D &operator*=(const Vector3D &other)
    {
        this->binaryAssignOp(other, std::multiplies<Content>());
        return *this;
    }

    Vector3D &operator/=(const Vector3D &other)
    {
        this->binaryAssignOp(other, std::divides<Content>());
        return *this;
    }
};

typedef Vector3D<double> Vector3Dd;

}
