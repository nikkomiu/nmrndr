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
    NMVector operator+(const NMVector &vector) const;
    NMVector operator-(const NMVector &vector) const;
    NMVector operator-() const;
    NMVector operator*(float scalar) const;
    NMVector operator/(float scalar) const;

    void operator+=(const NMVector &vector);
    void operator-=(const NMVector &vector);
    void operator*=(float scalar);
    void operator/=(float scalar);

    friend std::ostream &operator<<(std::ostream &os, const NMVector &vector)
    {
        os << std::fixed << std::setprecision(2);
        os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return os;
    }

    inline float SquaredMagnitude() const { return x * x + y * y + z * z; }

    inline float Magnitude() const { return std::sqrt(SquaredMagnitude()); }

    inline NMVector Normalized() const { return *this / Magnitude(); }

    void Normalize();

    float DotProduct(const NMVector &other) const;
    NMVector CrossProduct(const NMVector &other) const;

protected:

    float x;
    float y;
    float z;
};
