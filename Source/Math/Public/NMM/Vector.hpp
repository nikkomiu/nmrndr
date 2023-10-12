#pragma once

#include <cmath>
#include <iomanip>
#include <ostream>

#include "NMM/Util.hpp"

class NMPoint;
class NMTuple;

class NMVector
{
public:

    NMVector() : x(0.0f), y(0.0f), z(0.0f) {}
    NMVector(float x, float y, float z) : x(x), y(y), z(z) {}

    inline float GetX() const { return x; }
    inline float GetY() const { return y; }
    inline float GetZ() const { return z; }

    bool operator==(const NMVector &other) const
    {
        return nmmath::FloatEquals(x, other.x) && nmmath::FloatEquals(y, other.y) && nmmath::FloatEquals(z, other.z);
    }

    NMPoint operator+(const NMPoint &point) const;
    NMVector operator+(const NMVector &vector) const
    {
        return NMVector(x + vector.GetX(), y + vector.GetY(), z + vector.GetZ());
    }

    NMVector operator-(const NMVector &vector) const
    {
        return NMVector(x - vector.GetX(), y - vector.GetY(), z - vector.GetZ());
    }

    NMVector operator-() const { return NMVector(-x, -y, -z); }
    NMVector operator*(float scalar) const { return NMVector(x * scalar, y * scalar, z * scalar); }
    NMVector operator/(float scalar) const { return NMVector(x / scalar, y / scalar, z / scalar); }

    void operator+=(const NMVector &vector)
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
    }

    void operator-=(const NMVector &vector)
    {
        x -= vector.x;
        y -= vector.y;
        z -= vector.z;
    }

    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    void operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }

    friend std::ostream &operator<<(std::ostream &os, const NMVector &vector)
    {
        os << std::fixed << std::setprecision(7);
        os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return os;
    }

    inline float SquaredMagnitude() const { return x * x + y * y + z * z; }

    inline float Magnitude() const { return std::sqrt(SquaredMagnitude()); }

    inline NMVector Normalized() const { return *this / Magnitude(); }

    inline void Normalize() { *this /= Magnitude(); }

    inline float DotProduct(const NMVector &other) const { return x * other.x + y * other.y + z * other.z; }

    float DotProduct(const NMPoint &point) const;

    NMVector CrossProduct(const NMVector &other) const
    {
        return NMVector(y * other.GetZ() - z * other.GetY(), z * other.GetX() - x * other.GetZ(),
                        x * other.GetY() - y * other.GetX());
    }

    NMVector Reflect(const NMVector &normal) const { return *this - normal * 2.0f * DotProduct(normal); }

protected:

    float x;
    float y;
    float z;
};
