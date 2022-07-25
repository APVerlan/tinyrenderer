#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <array>
#include <cmath>
#include <iostream>

namespace geometry {

template <typename T>
struct Vector2 {
   public:
    union {
        struct {
            T u, v;
        };

        struct {
            T x, y;
        };

        std::array<T, 2> raw;
    };

   public:
    Vector2() : u(0), v(0) {}
    Vector2(T u, T v) : u(u), v(v) {}

    Vector2<T> operator+(const Vector2<T>& other) const { return Vector2<T>(u + other.u, v + other.v); }
    Vector2<T> operator-(const Vector2<T>& other) const { return Vector2<T>(u - other.u, v - other.v); }
    Vector2<T> operator*(float f) const { return Vector2<T>(u * f, v * f); }

    friend std::ostream& operator<<(std::ostream& s, const Vector2<T>& v);
};

template <class T>
struct Vector3 {
   public:
    union {
        struct {
            T x, y, z;
        };

        struct {
            T ivert, iuv, inorm;
        };

        std::array<T, 3> raw;
    };

   public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vector3<T> operator+(const Vector3<T>& other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vector3<T> operator-(const Vector3<T>& other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vector3<T> operator*(float f) const { return {x * f, y * f, z * f}; }

    friend std::ostream& operator<<(std::ostream& s, const Vector3<T>& v);

    float GetVectorNorm() const { return std::sqrt(x * x + y * y + z * z); }
    Vector3<T>& Normalize(T l = 1) {
        *this = (*this) * (l / GetVectorNorm());
        return *this;
    }

    friend T Vector3ScalarProduct(const Vector3<T>& lhs, const Vector3<T>& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    friend Vector3<T> Vector3CrossProduct(const Vector3<T>& lhs, const Vector3<T>& rhs) {
        return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
    }
};

template <class T>
std::ostream& operator<<(std::ostream& s, const Vector2<T>& v) {
    s << "(" << v.x << ", " << v.y << ")\n";
    return s;
}

template <class T>
std::ostream& operator<<(std::ostream& s, const Vector3<T>& v) {
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
    return s;
}

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

}  // namespace geometry

#endif  //__GEOMETRY_H__