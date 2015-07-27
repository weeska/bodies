#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

namespace wmath {

namespace operators {
template <typename Type>
Type addOp(const Type &lhs, const Type &rhs) {
    Type sum(lhs);
    sum += rhs;
    return std::move(sum);
}

template <typename Type>
Type subtractOp(const Type &lhs, const Type &rhs) {
    Type sum(lhs);
    sum -= rhs;
    return std::move(sum);
}

template <typename Type>
Type multOp(const Type &lhs, double factor) {
    Type product(lhs);
    product *= factor;
    return std::move(product);
}

template <typename Type, typename Func>
void binaryAssignOp(Type &lhs, const Type &rhs, Func f) {
    std::transform(std::begin(lhs), std::end(lhs),
                   std::begin(rhs), std::begin(lhs),
                   f);
}

}

template <class Content, int Size>
class Vector : public std::array<Content,Size>{
public:
    Vector()
        : std::array<Content, Size>()
    {
    }

    Vector operator+(const Vector &rhs) const {
        return std::move(operators::addOp(*this, rhs));
    }

    Vector operator-(const Vector &rhs) const {
        return std::move(operators::subtractOp(*this, rhs));
    }

    Vector &operator+=(const Vector &other) {
        operators::binaryAssignOp(*this, other, std::plus<Content>());
        return *this;
    }

    Vector &operator-=(const Vector &other) {
        operators::binaryAssignOp(*this, other, std::minus<Content>());
        return *this;
    }

    Vector &operator*=(Content factor) {
        std::transform(std::begin(*this), std::end(*this), std::begin(*this), [&](Content v){return v * factor;});
        return (*this);
    }

    Vector &operator/=(Content factor) {
        std::transform(std::begin(*this), std::end(*this), std::begin(*this), [&](Content v){return v / factor;});
        return (*this);
    }

    template <typename ResultType = double>
    ResultType sqr_length() const {
        auto sqr = [](Content acc, Content v) {return acc + v * v;};
        return std::accumulate(std::begin(*this), std::end(*this), ResultType(), sqr);
    }

    template <typename ResultType = double>
    ResultType length() const {
        return std::sqrt(this->sqr_length<ResultType>());
    }

    Vector &normalize() {
        const double length_ = this->length();
        std::transform(std::begin(*this), std::end(*this), std::begin(*this), [&](Content v){return v / length_;});
        return *this;
    }
};

template <typename Content>
class Vec2 : public Vector<Content, 2>
{
public:
    Vec2(Content x = Content(), Content y = Content())
    {
        (*this)[0] = x;
        (*this)[1] = y;
    }

    Vec2 operator+(const Vec2 &rhs) const {
        return std::move(operators::addOp(*this, rhs));
    }

    Vec2 operator-(const Vec2 &rhs) const {
        return std::move(operators::subtractOp(*this, rhs));
    }
};

template <typename Content>
class Vec3 : public Vector<Content, 3>
{
public:
    Vec3(Content x = Content(), Content y = Content(), Content z = Content())
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    }

    Vec3 operator+(const Vec3 &rhs) const {
        return std::move(operators::addOp(*this, rhs));
    }

    Vec3 operator-(const Vec3 &rhs) const {
        return std::move(operators::subtractOp(*this, rhs));
    }

    Vec3 operator*(double factor) const {
        return std::move(operators::multOp(*this, factor));
    }
};

template <typename Content>
class Vec4 : public Vector<Content, 4>
{
public:
    Vec4(Content x = Content(), Content y = Content(), Content z = Content(), Content w = Content())
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
        (*this)[3] = w;
    }

    Vec4 operator+(const Vec4 &rhs) const {
        return std::move(operators::addOp(*this, rhs));
    }

    Vec4 operator-(const Vec4 &rhs) const {
        return std::move(operators::subtractOp(*this, rhs));
    }
};

typedef Vec2<double> Vec2d;
typedef Vec3<double> Vec3d;
typedef Vec4<double> Vec4d;

}
